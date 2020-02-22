//
//  ZGCaptureDeviceProtocol.h
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/1/12.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_CustomVideoCapture

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ZGCaptureDevice;

@protocol ZGCaptureDeviceDataOutputPixelBufferDelegate <NSObject>

- (void)captureDevice:(id<ZGCaptureDevice>)device didCapturedData:(CVPixelBufferRef)data presentationTimeStamp:(CMTime)timeStamp;

@end


@protocol ZGCaptureDevice <NSObject>

@property (nonatomic, weak) id<ZGCaptureDeviceDataOutputPixelBufferDelegate> delegate;

- (void)startCapture;

- (void)stopCapture;

@end

NS_ASSUME_NONNULL_END

#endif // _Module_CustomVideoCapture
