//
//  ZegoExpressEngine+IM.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (IM)

/// 发送房间广播消息
/// @param message 消息内容，长度不超过256字节
/// @param roomID 房间 ID
/// @param callback 发送广播消息结果通知
- (void)sendBroadcastMessage:(NSString *)message roomID:(NSString *)roomID callback:(nullable ZegoIMSendBroadcastMessageCallback)callback;

/// 发送自定义信令
/// @param command 自定义信令内容，长度不超过256字节
/// @param toUserList 信令的接收者
/// @param roomID 房间 ID
/// @param callback 发送信令结果通知
- (void)sendCustomCommand:(NSString *)command toUserList:(nullable NSArray<ZegoUser *> *)toUserList roomID:(NSString *)roomID callback:(nullable ZegoIMSendCustomCommandCallback)callback;

@end

NS_ASSUME_NONNULL_END
