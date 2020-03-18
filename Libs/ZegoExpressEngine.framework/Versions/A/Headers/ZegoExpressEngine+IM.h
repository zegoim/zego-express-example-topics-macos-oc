//
//  ZegoExpressEngine+IM.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (IM)

/// Send room broadcast message
///
/// @param message Message content, no longer than 256 bytes
/// @param roomID Room ID
/// @param callback Send broadcast message result callback
- (void)sendBroadcastMessage:(NSString *)message roomID:(NSString *)roomID callback:(nullable ZegoIMSendBroadcastMessageCallback)callback;

/// Send room broadcast message
///
/// @param message Message content, no longer than 256 bytes
/// @param roomID Room ID
/// @param callback Send barrage message result callback
- (void)sendBarrageMessage:(NSString *)message roomID:(NSString *)roomID callback:(nullable ZegoIMSendBarrageMessageCallback)callback;

/// Send custom command
///
/// @param command Custom command content, no longer than 256 bytes
/// @param toUserList The users who will receive the command
/// @param roomID Room ID
/// @param callback Send commad result callback
- (void)sendCustomCommand:(NSString *)command toUserList:(nullable NSArray<ZegoUser *> *)toUserList roomID:(NSString *)roomID callback:(nullable ZegoIMSendCustomCommandCallback)callback;

@end

NS_ASSUME_NONNULL_END
