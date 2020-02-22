//
//  ZGCaptureDeviceCamera.h
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/1/12.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_CustomVideoCapture

#import <Foundation/Foundation.h>
#import "ZGCaptureDeviceProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZGCaptureDeviceCamera : NSObject <ZGCaptureDevice>

@property (nonatomic, weak) id<ZGCaptureDeviceDataOutputPixelBufferDelegate> delegate;

- (instancetype)initWithPixelFormatType:(OSType)pixelFormatType;

@end

NS_ASSUME_NONNULL_END

#endif // _Module_CustomVideoCapture
