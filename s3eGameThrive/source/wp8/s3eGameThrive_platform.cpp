/*
 * wp8-specific implementation of the s3eGameThrive extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include <crtdbg.h>

#include "s3eEdk.h"

#define _CRT_PERROR_DEFINED
#include <wrl/client.h>
#include <wrl/module.h>
#undef _CRT_PERROR_DEFINED

#include "s3eGameThrive_internal.h"
#include "s3eGameThrive_internal_wp8.h"

#include "s3eGameThrive_shim.h"
#include "IwDebug.h"

#define S3E_CURRENT_EXT			GAMETHRIVE
#define S3E_DEVICE_GAMETHRIVE	S3E_EXT_GAMETHRIVE_HASH

using namespace s3eGameThriveExtension;

s3eResult s3eGameThriveInit_platform()
{
    if (s3eGameThriveShim::GetInterface() == nullptr)
    {
        IwTrace(GAMETHRIVE, ("No IManagedS3Es3eGameThriveAPI interface. Managed part of s3eGameThrive extension failed to register."));
        return S3E_RESULT_ERROR;
    }

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eGameThriveTerminate_platform()
{
    // Add any platform-specific termination code here
}

void GameThriveInitialize_platform(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister)
{
    Platform::String^ appId_string = UTF8ToString(appId);

	// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, NOTIFICATION_RECEIVED, (s3eCallback)callbackFn, NULL, false);

    s3eGameThriveShim::GetInterface()->GameThriveInitialize_managed(appId_string);
}

void GameThriveSendTag_platform(const char* key, const char* value)
{
    Platform::String^ key_string = UTF8ToString(key);
    Platform::String^ value_string = UTF8ToString(value);
    s3eGameThriveShim::GetInterface()->GameThriveSendTag_managed(key_string, value_string);
}

void GameThriveGetTags_platform(GameThriveTagsReceivedCallbackFn callbackFn) {

	// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, TAGS_RECEIVED, (s3eCallback)callbackFn, NULL, false);

    s3eGameThriveShim::GetInterface()->GameThriveGetTags_managed();
}

void GameThriveDeleteTag_platform(const char* key)
{
    Platform::String^ key_string = UTF8ToString(key);
    s3eGameThriveShim::GetInterface()->GameThriveDeleteTag_managed(key_string);
}

void GameThriveSendPurchase_platform(const double* amount)
{
    s3eGameThriveShim::GetInterface()->GameThriveSendPurchase_managed(*amount);
}

void GameThriveGetIdsAvailable_platform(GameThriveIdsAvailableCallbackFn callbackFn) {

	// Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, IDS_AVAILABLE, (s3eCallback)callbackFn, NULL, false);

    s3eGameThriveShim::GetInterface()->GameThriveGetIdsAvailable_managed();
}

// Windows Phone Native SDK does this on its own
void GameThriveOnPause_platform() {
}
void GameThriveOnResume_platform() {
}

// Windows Phone Native SDK always registers for push
void GameThriveRegisterForPushNotifications_platform() {
}

void GameThriveEnableVibrate_platform() {
	// For Android Only
}

void GameThriveEnableSound_platform() {
	// For Android Only
}


// The following 3 functions are called from the shim which was called from the .NET CLR
void NotificationReceivedCallback(const char* additionalData, bool isActive) {

	GameThriveNotificationReceivedResult result;
	result.m_Message = NULL;
	result.m_AdditionalData = additionalData;
	result.m_isActive = isActive;

	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_NOTIFICATION_RECEIVED,
							&result,
							sizeof(result),
							NULL,
							S3E_FALSE); // FALSE, not a one shot callback.
}
void TagsReceivedCallback(const char* tags) {
	GameThriveTagsReceivedResult result;
	result.m_Tags = tags;
	
	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_TAGS_RECEIVED,
							&result,
							sizeof(result),
							NULL,
							S3E_TRUE); // TRUE, a one shot callback.
}

void IdsAvailableCallback(const char* playerID, const char* pushToken) {
	GameThriveIdsAvailableResult result;
	result.m_PlayerID = playerID;
	result.m_PushToken = pushToken;
	
	s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
							S3E_GAMETHRIVE_CALLBACK_IDS_AVAILABLE,
							&result,
							sizeof(result),
							NULL,
							S3E_FALSE); // FALSE, not a one shot callback.
}