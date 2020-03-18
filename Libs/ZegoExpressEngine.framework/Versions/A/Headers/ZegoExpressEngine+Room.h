//
//  ZegoExpressEngine+Room.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Room)

/// Login room. You must log in to the room before startPublishing and startPlayingStream the stream.
///
/// Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
/// Messages sent in one room (eg apis [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, ZegoExpressEngine does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
/// ZegoExpressEngine supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
/// If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
/// @param roomID Room ID, a string of up to 128 bytes in length
/// @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user;

/// Login room. You must log in to the room before startPublishing and startPlayingStream the stream.
///
/// To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter.
/// Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
/// Messages sent in one room (eg apis [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, ZegoExpressEngine does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
/// ZegoExpressEngine supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
/// If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
/// @param roomID Room ID, a string of up to 128 bytes in length
/// @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
/// @param config Advanced room configuration
- (void)loginRoom:(NSString *)roomID user:(ZegoUser *)user config:(ZegoRoomConfig *)config;

/// Logout room
///
/// Exiting the room will stop all publishing and playing streams for user, and then ZegoExpressEngine will auto stop local preview UI. After calling this interface, you will receive [onRoomStateUpdate] callback notification successfully exits the room, while other users in the same room will receive the [onRoomUserUpdate] callback notification.
/// @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
- (void)logoutRoom:(NSString *)roomID;

@end

NS_ASSUME_NONNULL_END
