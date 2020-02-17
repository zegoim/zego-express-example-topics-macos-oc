//
//  ZegoExpressEngine.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEventHandler.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine : NSObject

/// 创建引擎单例对象
/// @discussion 在调用其他 API 前需要先创建并初始化引擎；SDK 只支持创建一个 ZegoExpressEngine 实例，多次调用此接口返回的都是同一个对象。
/// @param appID ZEGO 为开发者签发的应用 ID，请从 ZEGO 管理控制台申请
/// @param appSign 每个 AppID 对应的应用签名，请从 ZEGO 管理控制台申请
/// @param isTestEnv 选择使用测试环境还是正式商用环境，正式环境需要在 ZEGO 管理控制台提交工单配置
/// @param scenario 所属的应用场景，当前请选择为 ZegoScenarioGeneral
/// @param eventHandler 事件通知回调。传空则意味着不接收任何回调通知。之后也可通过 addEventHandler:/RemoveHandler: 进行管理
/// @return 引擎单例对象
+ (ZegoExpressEngine *)createEngineWithAppID:(unsigned int)appID appSign:(NSString *)appSign isTestEnv:(BOOL)isTestEnv scenario:(ZegoScenario)scenario eventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// 销毁引擎单例对象
/// @discussion 用于释放 ZegoExpressEngine 使用的资源。
+ (void)destroyEngine;

/// 获取引擎单例对象
/// @discussion 如果引擎尚未创建或已经销毁，则返回 nil
/// @return 引擎单例对象
+ (nullable ZegoExpressEngine *)sharedEngine;

/// 设置引擎进阶配置，仅在创建引擎之前调用才生效
/// @param config 引擎进阶配置
+ (void)setEngineConfig:(ZegoEngineConfig *)config;

/// 添加事件通知代理，最多支持添加 16 个
/// @param eventHandler 事件通知代理
- (void)addEventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// 移除回调事件通知代理
/// @param eventHandler 事件通知代理
- (void)removeEventHandler:(nullable id<ZegoEventHandler>)eventHandler;

/// 获取 SDK 版本号
/// @return SDK 版本号
+ (NSString *)getVersion;

/// 上传日志到 ZEGO 服务器
- (void)uploadLog;

/// 设置调试详细信息开关以及语言
/// @discussion 默认开启且调试信息的语言为英文。
/// @param enable 详细调试信息开关
/// @param language 调试信息语种
- (void)setDebugVerbose:(BOOL)enable language:(ZegoLanguage)language;

/// 此方法不可用，请使用 `+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:`
+ (instancetype)new NS_UNAVAILABLE;

/// 此方法不可用，请使用 `+createEngineWithAppID:appSign:isTestEnv:scenario:eventHandler:`
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
