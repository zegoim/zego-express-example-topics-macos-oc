//
//  Version: 1.5.5.523_stable
//
//  ZegoExpressEngine.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEventHandler.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine : NSObject

/// Create engine singleton instance
///
/// The engine needs to be created and initialized before calling other APIs. The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this interface return the same object.
/// @param appID Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console https://console-express.zego.im/. The value ranges from 0 to 4294967295.
/// @param appSign Application signature for each AppID, please apply from the ZEGO Admin Console. Application signature is a 64 character string. Each character has a range of '0' ~ '9', 'a' ~ 'z'.
/// @param isTestEnv Choose to use a test environment or a formal commercial environment, the formal environment needs to submit work order configuration in the ZEGO management console. The test environment is for test development, with a limit of 30 rooms and 230 users. Official environment App is officially launched. ZEGO will provide corresponding server resources according to the configuration records submitted by the developer in the management console. The test environment and the official environment are two sets of environments and cannot be interconnected.
/// @param scenario The application scenario. Developers can choose one of ZegoScenario based on the scenario of the app they are developing, and the engine will preset a more general setting for specific scenarios based on the set scenario. After setting specific scenarios, developers can still call specific api to set specific parameters if they have customized parameter settings.
/// @param eventHandler Event notification callback. [nil] means not receiving any callback notifications.It can also be managed later via [setEventHandler]
/// @return Engine singleton instance
+ (ZegoExpressEngine *)createEngineWithAppID:(unsigned int)appID appSign:(NSString *)appSign isTestEnv:(BOOL)isTestEnv scenario:(ZegoScenario)scenario eventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// Destroy engine singleton object asynchronously
///
/// Used to release resources used by ZegoExpressEngine.
/// @param callback Notification callback for destroy engine completion. Developers can listen to this callback to ensure that device hardware resources are released. This callback is only used to notify the completion of the release of internal resources of the engine. Developers cannot release resources related to the engine within this callback. If the developer only uses SDK to implement audio and video functions, this parameter can be passed [nil].
+ (void)destroyEngine:(nullable ZegoDestroyCompletionCallback)callback;

/// Returns engine singleton instance
///
/// If the engine has not been created or has been destroyed, an unusable engine object will be returned.
/// @return Engine singleton instance
+ (ZegoExpressEngine *)sharedEngine;

/// Set the advanced engine configuration, which will only take effect before create engine
///
/// Developers need to call this interface to set advanced function configuration when they need advanced functions of the engine.
/// @param config Advanced engine configuration
+ (void)setEngineConfig:(ZegoEngineConfig *)config;

/// Get SDK version number
///
/// When the SDK is running, the developer finds that it does not match the expected situation and submits the problem and related logs to the ZEGO technical staff for locating. The ZEGO technical staff may need the information of the engine version to assist in locating the problem.
/// Developers can also collect this information as the version information of the engine used by the app, so that the SDK corresponding to each version of the app on the line.
/// @return SDK version
+ (NSString *)getVersion;

/// Set event notification callback, set [nil] to clears the set callback.
///
/// Invoke this function will override the callback passed in [createEngine].
/// @param eventHandler Event notification callback. Developers should override callback related methods to focus on specific notifications based on their own business scenarios. The main callback methods of SDK are in [IZegoEventHandler].
- (void)setEventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// Upload logs to ZEGO server
///
/// By default, SDK creates and prints log files in the app's default directory. Each log file defaults to a maximum of 5MB. Three log files are written over and over in a circular fashion. When calling this interface, SDK will auto package and upload the log files to the ZEGO server.
/// Developers can provide a business “feedback” channel in the app. When users feedback problems, they can call this interface to upload the local log information of SDK to help locate user problems.
- (void)uploadLog;

/// Set debug details switch and language
///
/// The debug switch is set to on and the language is English by default.
/// @param enable Detailed debugging information switch
/// @param language Debugging information language
- (void)setDebugVerbose:(BOOL)enable language:(ZegoLanguage)language;

/// This method is unavaialble
///
/// Please use [+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:] instead
+ (instancetype)new NS_UNAVAILABLE;

/// This method is unavaialble
///
/// Please use [+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:] instead
- (instancetype)init NS_UNAVAILABLE;

/// Destroy engine singleton instance
///
/// Used to release resources used by ZegoExpressEngine.
/// @deprecated This interface is deprecated, please use the overloaded interface with the same name
+ (void)destroyEngine DEPRECATED_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

#import "ZegoExpressEngine+Device.h"
#import "ZegoExpressEngine+CustomVideoIO.h"
#import "ZegoExpressEngine+IM.h"
#import "ZegoExpressEngine+Mixer.h"
#import "ZegoExpressEngine+Player.h"
#import "ZegoExpressEngine+Preprocess.h"
#import "ZegoExpressEngine+Publisher.h"
#import "ZegoExpressEngine+Room.h"
