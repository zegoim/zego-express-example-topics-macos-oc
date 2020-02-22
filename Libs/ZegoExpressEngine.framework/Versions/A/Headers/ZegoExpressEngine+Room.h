//
//  ZegoExpressEngine+Room.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Room)

/// Login room
/// @discussion You must log in to the room before pushing and pulling the stream, and users in the same room can talk to each other.If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally.You can get the current connection status of the local room by listening to the  onRoomStateUpdate:errorCode:room: delegate method, and other users in the same room will receive onRoomUserUpdate:userList:room: Callback notification.
/// @param roomID Room ID, a string of up to 256 bytes in length
/// @param user User object instance, configure user ID, username
/// @param config Room advanced configuration, the air will use the default configuration
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user config:(nullable ZegoRoomConfig *)config;

/// Login room
/// @discussion Use this interface if you have high security requirementsYou must log in to the room before publishing and playing the stream, and users in the same room can talk to each other.If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally.You can get the current connection status of the local room by listening to the onRoomStateUpdate:errorCode:room: delegate method, and other users in the same room will receive onRoomUserUpdate:userList:room: Callback notification.
/// @param roomID Room ID, a string of up to 256 bytes in length
/// @param user User object instance, configure user ID, username
/// @param config Room advanced configuration, the air will use the default configuration
/// @param token The token issued by the developer's business server is used to ensure security. The generation rules are detailed in https://doc.zego.im/CN/565.html
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user config:(nullable ZegoRoomConfig *)config token:(NSString *)token;

/// Logout room
/// @discussion Exiting the room will stop all publish and play streams for that user. After calling this interface, you will receive onRoomStateUpdate:errorCode:room: callback notification successfully exits the room, while other users in the same room will receive the onRoomUserUpdate:userList:room: callback notification.
/// @param roomID Room ID
- (void)logoutRoom:(NSString *)roomID;

@end

NS_ASSUME_NONNULL_END
