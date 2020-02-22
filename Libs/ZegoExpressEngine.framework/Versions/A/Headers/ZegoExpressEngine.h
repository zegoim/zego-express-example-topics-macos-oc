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
/// @discussion The engine needs to be created and initialized before calling other APIs. The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this interface return the same object.
/// @param appID Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console
/// @param appSign Application signature for each AppID, please apply from the ZEGO Admin Console
/// @param isTestEnv Choose to use a test environment or a formal commercial environment, the formal environment needs to submit work order configuration in the ZEGO management console
/// @param scenario The application scenario, currently selected as ZegoScenarioGeneral
/// @param eventHandler Event notification callback. Null means not receiving any callback notifications.   It can also be managed later via addEventHandler:/RemoveHandler:
/// @return Engine singleton instance
+ (ZegoExpressEngine *)createEngineWithAppID:(unsigned int)appID appSign:(NSString *)appSign isTestEnv:(BOOL)isTestEnv scenario:(ZegoScenario)scenario eventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// Destroy engine singleton instance
/// @discussion Used to release resources used by ZegoExpressEngine.
+ (void)destroyEngine;

/// Returns engine singleton instance
/// @discussion If the engine has not been created or has been destroyed, returns nil
/// @return Engine singleton instance
+ (nullable ZegoExpressEngine *)sharedEngine;

/// Set the advanced engine configuration, which will only take effect before create engine
/// @param config Advanced engine configuration
+ (void)setEngineConfig:(ZegoEngineConfig *)config;

/// Add event notification callback, up to 16 are supported
/// @param eventHandler Event notification delegate, can be null
- (void)addEventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// Remove event notification callback
/// @param eventHandler Event notification delegate, can be null
- (void)removeEventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// Get SDK version number
/// @return SDK version
+ (NSString *)getVersion;

/// Upload logs to ZEGO server
- (void)uploadLog;

/// Set debug details switch and language
/// @discussion The debug switch is set to on and the language is English by default.
/// @param enable Detailed debugging information switch
/// @param language Debugging information language
- (void)setDebugVerbose:(BOOL)enable language:(ZegoLanguage)language;

/// This method is unavaialble. Please use `+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:` instead
+ (instancetype)new NS_UNAVAILABLE;

/// This method is unavaialble. Please use `+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:` instead
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#import "ZegoExpressEngine+Device.h"
#import "ZegoExpressEngine+CustomVideoIO.h"
#import "ZegoExpressEngine+IM.h"
#import "ZegoExpressEngine+MediaPlayer.h"
#import "ZegoExpressEngine+Mixer.h"
#import "ZegoExpressEngine+Player.h"
#import "ZegoExpressEngine+Preprocess.h"
#import "ZegoExpressEngine+Publisher.h"
#import "ZegoExpressEngine+Room.h"
