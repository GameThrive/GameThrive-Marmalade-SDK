/*
Generic implementation of the s3eGameThrive extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eGameThrive_internal.h"
#include "s3eDevice.h"
#include "IwDebug.h"

int GameThriveSystemPaused(void* systemData, void* userData) {
	GameThriveOnPause_platform();
	return S3E_RESULT_SUCCESS;
}
 
int GameThriveSystemResume(void* systemData, void* userData) {
	GameThriveOnResume_platform();
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eGameThriveInit()
{
    //Add any generic initialisation code here
    return s3eGameThriveInit_platform();
}

void s3eGameThriveTerminate()
{
    //Add any generic termination code here
    s3eGameThriveTerminate_platform();
}

void GameThriveInitialize(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister)
{
	GameThriveInitialize_platform(appId, googleProjectNumber, callbackFn, autoRegister);
}

void GameThriveSendTag(const char* key, const char* value)
{
	GameThriveSendTag_platform(key, value);
}

void GameThriveGetTags(GameThriveTagsReceivedCallbackFn callbackFn)
{
	GameThriveGetTags_platform(callbackFn);
}

void GameThriveDeleteTag(const char* key)
{
	GameThriveDeleteTag_platform(key);
}

void GameThriveSendPurchase(const double* amount)
{
	GameThriveSendPurchase_platform(amount);
}

void GameThriveGetIdsAvailable(GameThriveIdsAvailableCallbackFn callbackFn)
{
	GameThriveGetIdsAvailable_platform(callbackFn);
}

void GameThriveRegisterForPushNotifications() {
	GameThriveRegisterForPushNotifications_platform();
}

void GameThriveEnableVibrate(s3eBool enable) {
	GameThriveEnableVibrate_platform(enable);
}

void GameThriveEnableSound(s3eBool enable) {
	GameThriveEnableSound_platform(enable);
}
