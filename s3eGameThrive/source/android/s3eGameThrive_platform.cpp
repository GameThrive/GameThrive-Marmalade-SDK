/*
 * android-specific implementation of the s3eGameThrive extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eGameThrive_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

#define S3E_CURRENT_EXT			GAMETHRIVE
#define S3E_DEVICE_GAMETHRIVE	S3E_EXT_GAMETHRIVE_HASH

static void NotificationReceivedCallback(JNIEnv* env, jobject _this, jstring m_Message, jstring m_AdditionalData, bool m_isActive);
static void TagsReceivedCallback(JNIEnv* env, jobject _this, jstring m_Tags);
static void IdsAvailableCallback(JNIEnv* env, jobject _this, jstring m_PlayerID, jstring m_PushToken);

static jobject g_Obj;
static jmethodID g_GameThriveInitialize;
static jmethodID g_GameThriveSendTag;
static jmethodID g_GameThriveGetTags;
static jmethodID g_GameThriveDeleteTag;
static jmethodID g_GameThriveSendPurchase;
static jmethodID g_GameThriveGetIdsAvailable;
static jmethodID g_GameThriveOnPause;
static jmethodID g_GameThriveOnResume;

s3eResult s3eGameThriveInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;
	
	const JNINativeMethod nativeMethodDefs[] =
	{
        {"NotificationReceivedCallback", "(Ljava/lang/String;Ljava/lang/String;Z)V", (void *)&NotificationReceivedCallback},
		{"TagsReceivedCallback", "(Ljava/lang/String;)V", (void *)&TagsReceivedCallback},
		{"IdsAvailableCallback", "(Ljava/lang/String;Ljava/lang/String;)V", (void *)&IdsAvailableCallback},
	};

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eGameThrive");
    if (!cls)
        goto fail;
	
	env->RegisterNatives(cls, nativeMethodDefs, sizeof(nativeMethodDefs)/sizeof(nativeMethodDefs[0]));

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_GameThriveInitialize = env->GetMethodID(cls, "GameThriveInitialize", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    if (!g_GameThriveInitialize)
        goto fail;

    g_GameThriveSendTag = env->GetMethodID(cls, "GameThriveSendTag", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_GameThriveSendTag)
        goto fail;

    g_GameThriveGetTags = env->GetMethodID(cls, "GameThriveGetTags", "()V");
    if (!g_GameThriveGetTags)
        goto fail;

    g_GameThriveDeleteTag = env->GetMethodID(cls, "GameThriveDeleteTag", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_GameThriveDeleteTag)
        goto fail;

    g_GameThriveSendPurchase = env->GetMethodID(cls, "GameThriveSendPurchase", "(D)V");
    if (!g_GameThriveSendPurchase)
        goto fail;

    g_GameThriveGetIdsAvailable = env->GetMethodID(cls, "GameThriveGetIdsAvailable", "()V");
    if (!g_GameThriveGetIdsAvailable)
        goto fail;
		
	g_GameThriveOnPause = env->GetMethodID(cls, "GameThriveOnPause", "()V");
    if (!g_GameThriveOnPause)
        goto fail;
	
	g_GameThriveOnResume = env->GetMethodID(cls, "GameThriveOnResume", "()V");
    if (!g_GameThriveOnResume)
        goto fail;

    IwTrace(GAMETHRIVE, ("GAMETHRIVE init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eGameThrive, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eGameThriveTerminate_platform()
{
    // Add any platform-specific termination code here
}

void GameThriveInitialize_platform(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring appId_jstr = env->NewStringUTF(appId);
    jstring googleProjectNumber_jstr = env->NewStringUTF(googleProjectNumber);
	
	// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, NOTIFICATION_RECEIVED, (s3eCallback)callbackFn, NULL, false);
	
    env->CallVoidMethod(g_Obj, g_GameThriveInitialize, appId_jstr, googleProjectNumber_jstr, autoRegister);
}

void NotificationReceivedCallback(JNIEnv* env, jobject _this, jstring m_Message, jstring m_AdditionalData, bool m_isActive) {
	const char* nativeMessageStr = NULL;
	const char* nativeAdditionalDataStr = NULL;
	
	if (m_Message != NULL)
		nativeMessageStr = env->GetStringUTFChars(m_Message, 0);
	if (m_AdditionalData != NULL)
		nativeAdditionalDataStr = env->GetStringUTFChars(m_AdditionalData, 0);
	
	GameThriveNotificationReceivedResult result;
	result.m_Message = nativeMessageStr;
	result.m_AdditionalData = nativeAdditionalDataStr;
	result.m_isActive = m_isActive;
	
	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_NOTIFICATION_RECEIVED,
							&result,
							sizeof(result),
							NULL,
							S3E_FALSE); // FALSE, not a one shot callback.
	
	// TODO: Fix very very small memory leak(1 KiBs or less).
	// 		 The 2 lines below fixes the leak however then the const char* pointer is invalid to the callback receiver.
	//env->ReleaseStringUTFChars(m_Message, nativeMessageStr);
	//env->ReleaseStringUTFChars(m_AdditionalData, nativeAdditionalDataStr);
}

void TagsReceivedCallback(JNIEnv* env, jobject _this, jstring m_Tags) {
	const char* nativeTagsStr = env->GetStringUTFChars(m_Tags, 0);
	
	GameThriveTagsReceivedResult result;
	result.m_Tags = nativeTagsStr;
	
	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_TAGS_RECEIVED,
							&result,
							sizeof(result),
							NULL,
							S3E_TRUE); // TRUE, a one shot callback.
	
	// TODO: Fix very very small memory leak(1 KiBs or less).
	// 		 The line below fixes the leak however then the const char* pointer is invalid to the callback receiver.
	//env->ReleaseStringUTFChars(m_Tags, nativeTagsStr);
}

void IdsAvailableCallback(JNIEnv* env, jobject _this, jstring m_PlayerID, jstring m_PushToken) {
	const char* nativePlayerIDStr = env->GetStringUTFChars(m_PlayerID, 0);
	const char* nativePushTokenStr = env->GetStringUTFChars(m_PushToken, 0);
	
	GameThriveIdsAvailableResult result;
	result.m_PlayerID = nativePlayerIDStr;
	result.m_PushToken = nativePushTokenStr;
	
	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_IDS_AVAILABLE,
							&result,
							sizeof(result),
							NULL,
							S3E_FALSE); // FALSE, not a one shot callback.
	
	// TODO: Fix very very small memory leak(1 KiBs or less).
	// 		 The 2 lines below fixes the leak however then the const char* pointer is invalid to the callback receiver.
	//env->ReleaseStringUTFChars(m_PlayerID, nativePlayerIDStr);
	//env->ReleaseStringUTFChars(m_PushToken, nativePushTokenStr);
}

void GameThriveSendTag_platform(const char* key, const char* value)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring key_jstr = env->NewStringUTF(key);
    jstring value_jstr = env->NewStringUTF(value);
	
    env->CallVoidMethod(g_Obj, g_GameThriveSendTag, key_jstr, value_jstr);
}

void GameThriveGetTags_platform(GameThriveTagsReceivedCallbackFn callbackFn)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
	
	// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, TAGS_RECEIVED, (s3eCallback)callbackFn, NULL, false);
	
    env->CallVoidMethod(g_Obj, g_GameThriveGetTags);
}

void GameThriveDeleteTag_platform(const char* key)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring key_jstr = env->NewStringUTF(key);
    env->CallVoidMethod(g_Obj, g_GameThriveDeleteTag, key_jstr);
}

void GameThriveSendPurchase_platform(const double* amount)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_GameThriveSendPurchase, *amount);
}

void GameThriveGetIdsAvailable_platform(GameThriveIdsAvailableCallbackFn callbackFn)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
	
		// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, IDS_AVAILABLE, (s3eCallback)callbackFn, NULL, false);
	
    env->CallVoidMethod(g_Obj, g_GameThriveGetIdsAvailable);
}

void GameThriveOnPause_platform() {
	JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_GameThriveOnPause);
}

void GameThriveOnResume_platform() {
	JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_GameThriveOnResume);
}

void GameThriveRegisterForPushNotifications_platform() {
	// On Android we always auto register for push notifications.
}