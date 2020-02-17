//
//  ZegoExpressEngine+CustomVideoIO.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (CustomVideoIO)

/// 设置自定义视频渲染回调
/// @param handler 自定义视频渲染回调对象
- (void)setCustomVideoRenderHandler:(nullable id<ZegoCustomVideoRenderHandler>)handler;

/// 设置自定义视频采集回调
/// @param handler 自定义视频采集回调对象
- (void)setCustomVideoCaptureHandler:(nullable id<ZegoCustomVideoCaptureHandler>)handler;

/// 向 SDK 发送自定义采集的视频帧 CVPixelBuffer 数据
/// @param buffer 要向 SDK 发送的视频帧数据
/// @param timeStamp 该视频帧的时间戳
- (void)sendCustomVideoCapturePixelBuffer:(CVPixelBufferRef)buffer timeStamp:(CMTime)timeStamp;

/// 向 SDK 发送自定义采集的视频帧 Texture 数据
/// @param textureID 纹理 ID
/// @param size 视频帧的画面宽高
/// @param timeStamp 该视频帧的时间戳
- (void)sendCustomVideoCaptureTextureData:(GLuint)textureID size:(CGSize)size timeStamp:(CMTime)timeStamp;

/// 设置自定义视频采集画面缩放填充模式
/// @param mode 画面填充缩放模式
- (void)setCustomVideoCaptureFillMode:(ZegoViewMode)mode;

@end

NS_ASSUME_NONNULL_END
