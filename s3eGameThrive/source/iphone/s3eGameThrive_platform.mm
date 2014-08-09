/*
 * iphone-specific implementation of the s3eGameThrive extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eGameThrive_internal.h"
#import "GameThrive.h"
#import <objc/runtime.h>
#import <UIKit/UIKit.h>

#define S3E_CURRENT_EXT			GAMETHRIVE
#define S3E_DEVICE_GAMETHRIVE	S3E_EXT_GAMETHRIVE_HASH

#include "s3eEdkError.h"

GameThrive* gameThrive;

NSString* CreateNSString(const char* string) {
    return [NSString stringWithUTF8String: string ? string : ""];
}

static char* CopyToCString(NSString* string) {
	if (string) {
		const char* pStr = [string UTF8String];
		char* pCopy = (char*) s3eEdkMallocOS(strlen(pStr) + 1);
		if (pCopy) {
			strcpy(pCopy, pStr);
			return pCopy;
		}
	}

	return NULL;
}



@implementation UIApplication(GameThrivePush)

NSDictionary* launchDict;



static void switchMethods(Class inClass, SEL oldSel, SEL newSel, IMP impl, const char* sig)
{
    class_addMethod(inClass, newSel, impl, sig);
    method_exchangeImplementations(class_getInstanceMethod(inClass, oldSel), class_getInstanceMethod(inClass, newSel));
}

+ (void)load {
    method_exchangeImplementations(class_getInstanceMethod(self, @selector(setDelegate:)), class_getInstanceMethod(self, @selector(setGameThriveDelegate:)));
}

- (void) setGameThriveDelegate:(id<UIApplicationDelegate>)delegate {
    static Class delegateClass = nil;
    
	if(delegateClass == [delegate class]) {
		[self setGameThriveDelegate:delegate];
		return;
	}
    
	delegateClass = [delegate class];
    
	switchMethods(delegateClass, @selector(application:didRegisterForRemoteNotificationsWithDeviceToken:),
                  @selector(application:blankMethod:), (IMP)didRegisterForRemoteNotificationsWithDeviceToken_GTLocal, "v@:::");
    
    switchMethods(delegateClass, @selector(application:didReceiveRemoteNotification:),
                  @selector(application:blankMethod2:), (IMP)didReceiveRemoteNotification_GTLocal, "v@:::");
    
    switchMethods(delegateClass, @selector(application:didFinishLaunchingWithOptions:),
                  @selector(application:selectorDidFinishLaunchingWithOptions:), (IMP)didFinishLaunchingWithOptions_GTLocal, "v@:::");
    
    [self setGameThriveDelegate:delegate];
}

void didRegisterForRemoteNotificationsWithDeviceToken_GTLocal(id self, SEL _cmd, id application, id deviceToken) {
    NSLog(@"Device Registered with Apple!");
    [gameThrive registerDeviceToken:deviceToken onSuccess:^(NSDictionary* results) {
        NSLog(@"Device Registered with GameThrive.");
    } onFailure:^(NSError* error) {
        NSLog(@"Device Registion Error with GameThrive: %@", error);
    }];
}

BOOL didFinishLaunchingWithOptions_GTLocal(id self, SEL _cmd, id application, id launchOptions) {
    launchDict = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
    
    BOOL result = YES;
    
	if ([self respondsToSelector:@selector(application:selectorDidFinishLaunchingWithOptions:)]) {
		if (![self application:application selectorDidFinishLaunchingWithOptions:launchOptions])
            result = NO;
    }
    else {
		[self applicationDidFinishLaunching:application];
		result = YES;
	}
    
	return result;
}

void didReceiveRemoteNotification_GTLocal(id self, SEL _cmd, id application, id userInfo) {
    processNotificationOpened(userInfo, [application applicationState] == UIApplicationStateActive);
}

const char* dictionaryToJsonChar(NSDictionary* dictionaryToConvert) {
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:dictionaryToConvert options:0 error:nil];
    NSString* jsonRequestData = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    
    return [jsonRequestData UTF8String];
}

void processNotificationOpened(NSDictionary* messageData, BOOL isActive) {
    [gameThrive notificationOpened:messageData];
    
    GameThriveNotificationReceivedResult result;
	result.m_Message = CopyToCString([gameThrive getMessageString]);
	
    NSDictionary* additionalData = [gameThrive getAdditionalData];
    if (additionalData)
        result.m_AdditionalData = dictionaryToJsonChar(additionalData);
	result.m_isActive = isActive;
    
    s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
                           S3E_GAMETHRIVE_CALLBACK_NOTIFICATION_RECEIVED,
                           &result,
                           sizeof(result),
                           NULL,
                           S3E_FALSE); // FALSE, not a one shot callback.
}

@end


s3eResult s3eGameThriveInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eGameThriveTerminate_platform()
{
    // Add any platform-specific termination code here
}

void GameThriveInitialize_platform(const char* appId, const char* googleProjectNumber, GameThriveNotificationReceivedCallbackFn callbackFn, s3eBool autoRegister) {
    
    gameThrive = [[GameThrive alloc] init:CreateNSString(appId) autoRegister:autoRegister];
    
    // Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, NOTIFICATION_RECEIVED, (s3eCallback)callbackFn, NULL, false);
    
    if (launchDict)
        processNotificationOpened(launchDict, false);
}

void GameThriveSendTag_platform(const char* key, const char* value) {
    [gameThrive sendTag:CreateNSString(key) value:CreateNSString(value)];
}

void GameThriveGetTags_platform(GameThriveTagsReceivedCallbackFn callbackFn) {
    // Register Callback
    EDK_CALLBACK_REG(GAMETHRIVE, TAGS_RECEIVED, (s3eCallback)callbackFn, NULL, false);
    
    [gameThrive getTags:^(NSDictionary* tags) {
        GameThriveTagsReceivedResult result;
        result.m_Tags = dictionaryToJsonChar(tags);
        
        s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
                               S3E_GAMETHRIVE_CALLBACK_TAGS_RECEIVED,
                               &result,
                               sizeof(result),
                               NULL,
                               S3E_TRUE); // TRUE, a one shot callback.
    }];

}

void GameThriveDeleteTag_platform(const char* key) {
    [gameThrive deleteTag:CreateNSString(key)];
}

void GameThriveSendPurchase_platform(const double* amount) {
    [gameThrive sendPurchase:[NSNumber numberWithDouble:*amount]];
}

void GameThriveGetIdsAvailable_platform(GameThriveIdsAvailableCallbackFn callbackFn) {
    EDK_CALLBACK_REG(GAMETHRIVE, IDS_AVAILABLE, (s3eCallback)callbackFn, NULL, false);
    
    [gameThrive IdsAvailable:^(NSString* playerId, NSString* pushToken) {
        GameThriveIdsAvailableResult result;
        result.m_PlayerID = CopyToCString(playerId);
        result.m_PushToken = CopyToCString(pushToken);
        
        s3eEdkCallbacksEnqueue(S3E_DEVICE_GAMETHRIVE,
                               S3E_GAMETHRIVE_CALLBACK_IDS_AVAILABLE,
                               &result,
                               sizeof(result),
                               NULL,
                               S3E_FALSE); // FALSE, not a one shot callback.
    }];
}

void GameThriveOnResume_platform() {
    [gameThrive onFocus:@"resume"];
}

void GameThriveOnPause_platform() {
    [gameThrive onFocus:@"suspend"];
}

void GameThriveRegisterForPushNotifications_platform() {
  [gameThrive registerForPushNotifications];
}