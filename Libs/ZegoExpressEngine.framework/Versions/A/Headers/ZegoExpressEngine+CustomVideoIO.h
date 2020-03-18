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
/// @param handler Custom video render handler
- (void)setCustomVideoRenderHandler:(nullable id<ZegoCustomVideoRenderHandler>)handler;

/// Set the custom video capture handler
///
/// @param handler Custom video capture handler
- (void)setCustomVideoCaptureHandler:(nullable id<ZegoCustomVideoCaptureHandler>)handler;

/// Send texture video frame data to SDK
///
/// @param textureID texture ID
/// @param size Video frame width and height
/// @param timeStamp Timestamp of this video frame
- (void)sendCustomVideoCaptureTextureData:(GLuint)textureID size:(CGSize)size timeStamp:(CMTime)timeStamp;

/// Send texture video frame data to SDK
///
/// @param textureID texture ID
/// @param size Video frame width and height
/// @param timeStamp Timestamp of this video frame
/// @param channel Publishing stream channel.
- (void)sendCustomVideoCaptureTextureData:(GLuint)textureID size:(CGSize)size timeStamp:(CMTime)timeStamp channel:(ZegoPublishChannel)channel;

/// Send texture video frame data to SDK
///
/// @param buffer Video frame data to send to the SDK
/// @param timeStamp Timestamp of this video frame
- (void)sendCustomVideoCapturePixelBuffer:(CVPixelBufferRef)buffer timeStamp:(CMTime)timeStamp;

/// Send texture video frame data to SDK
///
/// @param buffer Video frame data to send to the SDK
/// @param timeStamp Timestamp of this video frame
/// @param channel Publishing stream channel.
- (void)sendCustomVideoCapturePixelBuffer:(CVPixelBufferRef)buffer timeStamp:(CMTime)timeStamp channel:(ZegoPublishChannel)channel;

/// Set custom video capture fill mode
///
/// @param mode View mode
- (void)setCustomVideoCaptureFillMode:(ZegoViewMode)mode;

/// Set custom video capture fill mode
///
/// @param mode View mode
/// @param channel Publishing stream channel.
- (void)setCustomVideoCaptureFillMode:(ZegoViewMode)mode channel:(ZegoPublishChannel)channel;

@end

NS_ASSUME_NONNULL_END
