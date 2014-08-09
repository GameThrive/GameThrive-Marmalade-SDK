/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_GAMETHRIVE_H
#define S3E_EXT_GAMETHRIVE_H

/**
 * @addtogroup s3egroup
 * @{
 */

/**
 * @defgroup edkgamethriveapigroup Android Basic Extension API Reference
 *
 * This extension has a single function that adds two integers. It is intended as a simple
 * demonstration for making Android extensions.
 *
 * This is an example extension supplied with the EDK. It is included to
 * demonstrate the implementation of an Android functionality and is not intended
 * for use in commercial applications.
 *
 * @{
 */

#include <s3eTypes.h>

typedef enum s3eGameThriveCallback
{
	S3E_GAMETHRIVE_CALLBACK_NOTIFICATION_RECEIVED,
	S3E_GAMETHRIVE_CALLBACK_TAGS_RECEIVED,
	S3E_GAMETHRIVE_CALLBACK_IDS_AVAILABLE,
	S3E_GAMETHRIVE_CALLBACK_MAX
} s3eGameThriveCallback;

typedef struct GameThriveNotificationReceivedResult
{
	const char*		m_Message;
	const char*		m_AdditionalData;
	s3eBool			m_isActive;

} GameThriveNotificationReceivedResult;

typedef struct GameThriveTagsReceivedResult
{
	const char*	m_Tags;
} GameThriveTagsReceivedResult;

typedef struct GameThriveIdsAvailableResult
{
	const char*	m_PlayerID;
	const char*	m_PushToken;
} GameThriveIdsAvailableResult;

typedef void (*GameThriveNotificationReceivedCallbackFn)(GameThriveNotificationReceivedResult* result, void* userData);
typedef void (*GameThriveTagsReceivedCallbackFn)(GameThriveTagsReceivedResult* result, void* userData);
typedef void (*GameThriveIdsAvailableCallbackFn)(GameThriveIdsAvailableResult* result, void* userData);
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the GameThrive extension is available.
 */
s3eBool s3eGameThriveAvailable();

void GameThriveInitialize(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister);

void GameThriveSendTag(const char* key, const char* value);

void GameThriveGetTags(GameThriveTagsReceivedCallbackFn callbackFn);

void GameThriveDeleteTag(const char* key);

void GameThriveSendPurchase(const double* amount);

void GameThriveGetIdsAvailable(GameThriveIdsAvailableCallbackFn callbackFn);

int GameThriveSystemPaused(void* systemData, void* userData);

int GameThriveSystemResume(void* systemData, void* userData);

void GameThriveRegisterForPushNotifications();

S3E_END_C_DECL

/** @} */
/** @} */

#endif /* !S3E_EXT_GAMETHRIVE_H */
