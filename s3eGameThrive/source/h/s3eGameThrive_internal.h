/*
 * Internal header for the s3eGameThrive extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EGAMETHRIVE_INTERNAL_H
#define S3EGAMETHRIVE_INTERNAL_H

#include "s3eTypes.h"
#include "s3eGameThrive.h"
#include "s3eGameThrive_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eGameThriveInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eGameThriveInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eGameThriveTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eGameThriveTerminate_platform();
void GameThriveInitialize_platform(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister);

void GameThriveSendTag_platform(const char* key, const char* value);

void GameThriveGetTags_platform(GameThriveTagsReceivedCallbackFn callbackFn);

void GameThriveDeleteTag_platform(const char* key);

void GameThriveSendPurchase_platform(const double* amount);

void GameThriveGetIdsAvailable_platform(GameThriveIdsAvailableCallbackFn callbackFn);

int GameThriveSystemPaused_platform(void* systemData, void* userData);

int GameThriveSystemResume_platform(void* systemData, void* userData);

void GameThriveOnPause_platform();

void GameThriveOnResume_platform();

void GameThriveRegisterForPushNotifications_platform();

void GameThriveEnableVibrate_platform(s3eBool enable);

void GameThriveEnableSound_platform(s3eBool enable);


#endif /* !S3EGAMETHRIVE_INTERNAL_H */