//
//  ZegoExpressEngine+CustomVideoIO.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (CustomVideoIO)

/// Set the custom video render handler
///
/// Custom video render, developers are responsible for rendering video data to UI components. This feature is generally used by developers who use third-party beauty features or use third-party rendering frameworks.
/// When you use the advanced features of ZegoExpressEngine's custom video render, you need to call this api to set a callback object for developers to transfer video data.
/// When you call the start preview [startPreview], start publishing stream [startPublishingStream], or start playing stream [startPlayingStream], the callback method that transfer video data to you will be triggered.
/// You can render video images according to the callback of SDK transfering video data.
/// Custom video rendering can be used with custom video capture.
/// @param handler Custom video render handler
- (void)setCustomVideoRenderHandler:(nullable id<ZegoCustomVideoRenderHandler>)handler;

/// Set the custom video capture handler
///
/// Custom video capture, that is, the developer is responsible for collecting video data and sending the collected video data to SDK for video data encoding and publishing to the ZEGO audio and video cloud.This feature is generally used by developers who use third-party beauty features or record game screen living.
/// When you use the advanced features of ZegoExpressEngine's custom video capture, you need to call this api to set SDK to notify that you can start sending video data to ZegoExpressEngine.
/// When you calls startPreview and startPublishingStream, a callback method that notifies you to start sending video data will be triggered. When you stop preview [stopPreview] and stop publishing stream [stopPublishingStream], it will trigger a callback method that notify that you can stop sending video data.
/// Because when using custom video capture, SDK will no longer start the camera to capture video data. You need to collect video data from video sources by yourself.
/// Custom video capture can be used with custom video rendering.
/// @param handler Custom video capture handler
- (void)setCustomVideoCaptureHandler:(nullable id<ZegoCustomVideoCaptureHandler>)handler;

/// Send texture video frame data to SDK
///
/// This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
/// @param textureID texture ID
/// @param size Video frame width and height
/// @param timeStamp Timestamp of this video frame
- (void)sendCustomVideoCaptureTextureData:(GLuint)textureID size:(CGSize)size timeStamp:(CMTime)timeStamp;

/// Send texture video frame data to SDK. You can call this api when publishing another streams.
///
/// This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
/// @param textureID texture ID
/// @param size Video frame width and height
/// @param timeStamp Timestamp of this video frame
/// @param channel Publishing stream channel.
- (void)sendCustomVideoCaptureTextureData:(GLuint)textureID size:(CGSize)size timeStamp:(CMTime)timeStamp channel:(ZegoPublishChannel)channel;

/// Send texture video frame data to SDK
///
/// This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
/// @param buffer Video frame data to send to the SDK
/// @param timeStamp Timestamp of this video frame
- (void)sendCustomVideoCapturePixelBuffer:(CVPixelBufferRef)buffer timeStamp:(CMTime)timeStamp;

/// Send texture video frame data to SDK. You can call this api when publishing another streams.
///
/// This api need to be start called after the [onStart] callback notification and to be stop called call after the [onStop] callback notification.
/// @param buffer Video frame data to send to the SDK
/// @param timeStamp Timestamp of this video frame
/// @param channel Publishing stream channel.
- (void)sendCustomVideoCapturePixelBuffer:(CVPixelBufferRef)buffer timeStamp:(CMTime)timeStamp channel:(ZegoPublishChannel)channel;

/// Set custom video capture fill mode
///
/// @param mode View mode
- (void)setCustomVideoCaptureFillMode:(ZegoViewMode)mode;

/// Set custom video capture fill mode. You can call this api when publishing another streams.
///
/// @param mode View mode
/// @param channel Publishing stream channel.
- (void)setCustomVideoCaptureFillMode:(ZegoViewMode)mode channel:(ZegoPublishChannel)channel;

@end

NS_ASSUME_NONNULL_END
