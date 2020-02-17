//
//  ZegoExpressEngine+Room.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Room)

/// 登录房间
/// @discussion 推拉流前必须登录房间，在同一个房间内的用户可以相互通话如果由于网络质量原因导致网络临时中断，SDK 内部会自动进行重连可通过监听 onRoomStateUpdate:errorCode:room: 代理方法获取本端当前房间连接状态的变化情况，同时同房间其他用户会接收到 onRoomUserUpdate:userList:room: 回调通知。
/// @param roomID 房间ID，最大长度为256字节的字符串
/// @param user 用户对象实例，配置用户 ID、用户名
/// @param config 房间高级配置，传空将使用默认配置
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user config:(nullable ZegoRoomConfig *)config;

/// 登录房间
/// @discussion 如果有较高的安全需求请使用此接口推拉流前必须登录房间，在同一个房间内的用户可以相互通话如果由于网络质量原因导致网络临时中断，SDK 内部会自动进行重连可通过监听 onRoomStateUpdate:errorCode:room: 代理方法获取本端当前房间连接状态的变化情况，同时同房间其他用户会接收到 onRoomUserUpdate:userList:room: 回调通知。
/// @param roomID 房间ID，最大长度为256字节的字符串
/// @param user 用户对象实例，配置用户 ID、用户名
/// @param config 房间高级配置，传空将使用默认配置
/// @param token 由开发者业务服务器下发的 token，用以保证安全性，生成规则详见 https://doc.zego.im/CN/565.html
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user config:(nullable ZegoRoomConfig *)config token:(NSString *)token;

/// 退出房间
/// @discussion 退出房间会停止该用户的所有推拉流，调用该接口后会收到 onRoomStateUpdate:errorCode:room: 回调通知成功退出房间，同时同房间其他用户会接收到 onRoomUserUpdate:userList:room: 回调通知。
/// @param roomID 用户已登录的房间 ID
- (void)logoutRoom:(NSString *)roomID;

@end

NS_ASSUME_NONNULL_END
