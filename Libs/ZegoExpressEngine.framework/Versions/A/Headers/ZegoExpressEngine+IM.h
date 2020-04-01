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
/// The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
/// Users of up to the first 500 advanced rooms in the same room can receive it, which is generally used when the number of live broadcast rooms is less than 500.
/// @param message Message content, no longer than 256 bytes
/// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
/// @param callback Send broadcast message result callback
- (void)sendBroadcastMessage:(NSString *)message roomID:(NSString *)roomID callback:(nullable ZegoIMSendBroadcastMessageCallback)callback;

/// Send room barrage message
///
/// There is no limit on the number of transmissions, but the server will actively drop messages if it is sent too frequently.
/// It can be received by users with more than 500 people in the same room, but it is not reliable, that is, when there are many users in the room or messages are sent frequently between users, the users who receive the messages may not be able to receive them. Generally used for sending live barrage.
/// @param message Message content, no longer than 256 bytes
/// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
/// @param callback Send barrage message result callback
- (void)sendBarrageMessage:(NSString *)message roomID:(NSString *)roomID callback:(nullable ZegoIMSendBarrageMessageCallback)callback;

/// Send custom command
///
/// The total sending frequency limit of [sendBroadcastMessage] and [sendCustomCommand] is 600 times per minute by default.
/// The type of point-to-point signaling in the same room is generally used for remote control signaling or message sending between users.
/// @param command Custom command content, no longer than 256 bytes
/// @param toUserList The users who will receive the command
/// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'
/// @param callback Send command result callback
- (void)sendCustomCommand:(NSString *)command toUserList:(nullable NSArray<ZegoUser *> *)toUserList roomID:(NSString *)roomID callback:(nullable ZegoIMSendCustomCommandCallback)callback;

@end

NS_ASSUME_NONNULL_END
