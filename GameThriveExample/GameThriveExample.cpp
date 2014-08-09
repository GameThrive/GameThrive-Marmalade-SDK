/**
 * @page GameThrive Test Application
 *
 * The test application demonstrates how to use the GameThrive push notification extension.
 *
 * MKB:
 * @include GameThriveExample.mkb
 *
 * Source:
 * @include GameThriveExample.cpp
 */

#include "s3eGameThrive.h"
#include "s3eDevice.h"
#include "s3ePointer.h"
#include "s3eSurface.h"
#include "s3eTimer.h"
#include "IwDebug.h"

static void HandleReceivedNotification(GameThriveNotificationReceivedResult* result, void* userData) {
	char buffer[1024];
	sprintf(buffer, "NOTIFICATION RECIEVED CALLBACK MESSAGE: %s", result->m_Message);
	s3eDebugOutputString(buffer);
	
	if (result->m_AdditionalData != NULL) {
		char buffer2[1024];
		sprintf(buffer2, "NOTIFICATION RECIEVED CALLBACK ADDITIONALDATA: %s", result->m_AdditionalData);
		s3eDebugOutputString(buffer2);
	}
}

S3E_MAIN_DECL int main() {
	GameThriveInitialize("5eb5a37e-b458-11e3-ac11-000c2940e62c", "703322744261", (GameThriveNotificationReceivedCallbackFn)HandleReceivedNotification, true);
	s3eDeviceRegister(S3E_DEVICE_PAUSE, &GameThriveSystemPaused, NULL);
	s3eDeviceRegister(S3E_DEVICE_UNPAUSE, &GameThriveSystemResume, NULL);
	
    while (!s3eDeviceCheckQuitRequest()) {
        s3eDeviceYield(0);
        s3eDebugPrint(0, 10, "GameThriveExample", 0);
		s3eDebugPrint(0, 30, "See logcat or Xcode console for debug info.", 0);

        s3eSurfaceShow();
    }
    return 0;
}
