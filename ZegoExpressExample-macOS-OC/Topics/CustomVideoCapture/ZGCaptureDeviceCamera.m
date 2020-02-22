//
//  ZGCaptureDeviceCamera.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/1/12.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_CustomVideoCapture

#import "ZGCaptureDeviceCamera.h"

@interface ZGCaptureDeviceCamera () <AVCaptureVideoDataOutputSampleBufferDelegate> {
    dispatch_queue_t _sampleBufferCallbackQueue;
}

@property (nonatomic, assign) OSType pixelFormatType;
@property (nonatomic, strong) AVCaptureDeviceInput *input;
@property (nonatomic, strong) AVCaptureVideoDataOutput *output;
@property (nonatomic, strong) AVCaptureSession *session;

@property (nonatomic, assign) BOOL isRunning;

@end

@implementation ZGCaptureDeviceCamera

- (instancetype)initWithPixelFormatType:(OSType)pixelFormatType {
    self = [super init];
    if (self) {
        self.pixelFormatType = pixelFormatType;
        _sampleBufferCallbackQueue = dispatch_queue_create("im.zego.ZGCustomVideoCaptureCameraDevice.outputCallbackQueue", DISPATCH_QUEUE_SERIAL);
    }
    return self;
}

- (void)dealloc {
//    [self stopCapture];
}


- (void)startCapture {
    ZGLogInfo(@" ▶️ Camera start to capture");
    if (self.isRunning) {
        return;
    }
    
    [self.session beginConfiguration];
    
    if ([self.session canSetSessionPreset:AVCaptureSessionPresetHigh]) {
        [self.session setSessionPreset:AVCaptureSessionPresetHigh];
    }
    
    AVCaptureDeviceInput *input = self.input;
    
    if ([self.session canAddInput:input]) {
        [self.session addInput:input];
    }
    
    
    AVCaptureVideoDataOutput *output = self.output;
    
    if ([self.session canAddOutput:output]) {
        [self.session addOutput:output];
    }
    
    AVCaptureConnection *captureConnection = [output connectionWithMediaType:AVMediaTypeVideo];
    
    if (input.device.position == AVCaptureDevicePositionFront) {
        captureConnection.videoMirrored = YES;
    }
    
    if (captureConnection.isVideoOrientationSupported) {
        captureConnection.videoOrientation = AVCaptureVideoOrientationPortrait;
    }
    
    [self.session commitConfiguration];
    
    if (!self.session.isRunning) {
        [self.session startRunning];
    }
    
    self.isRunning = YES;
    ZGLogInfo(@" ⏺ Camera has started capturing");
}

- (void)stopCapture {
    ZGLogInfo(@" ⏸ Camera stops capture");
    if (!self.isRunning) {
        return;
    }
    
    if (self.session.isRunning) {
        [self.session stopRunning];
    }
    
    self.isRunning = NO;
    ZGLogInfo(@" ⏹ Camera has stopped capturing");
}


#pragma mark - Getter

- (AVCaptureSession *)session {
    if (!_session) {
        _session = [[AVCaptureSession alloc] init];
    }
    return _session;
}

- (AVCaptureDeviceInput *)input {
    if (!_input) {
            NSArray *cameras= [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
            
    #if TARGET_OS_OSX
            // Note: This demonstration selects the last camera. Developers should choose the appropriate camera device by themselves.
            AVCaptureDevice *camera = cameras.lastObject;
            if (!camera) {
                NSLog(@"Failed to get camera");
                return nil;
            }
    #elif TARGET_OS_IOS
            // Note: This demonstration selects the front camera. Developers should choose the appropriate camera device by themselves.
            NSArray *captureDeviceArray = [cameras filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"position == %d", AVCaptureDevicePositionFront]];
            if (captureDeviceArray.count == 0) {
                NSLog(@"Failed to get camera");
                return nil;
            }
            AVCaptureDevice *camera = captureDeviceArray.firstObject;
    #endif
            
            NSError *error = nil;
            AVCaptureDeviceInput *captureDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:camera error:&error];
            if (error) {
                NSLog(@"Conversion of AVCaptureDevice to AVCaptureDeviceInput failed");
                return nil;
            }
            _input = captureDeviceInput;
        }
        return _input;
}

- (AVCaptureVideoDataOutput *)output {
    if (!_output) {
        AVCaptureVideoDataOutput *videoDataOutput = [[AVCaptureVideoDataOutput alloc] init];
        videoDataOutput.videoSettings = @{(id)kCVPixelBufferPixelFormatTypeKey:@(self.pixelFormatType)};
        [videoDataOutput setSampleBufferDelegate:self queue:_sampleBufferCallbackQueue];
        _output = videoDataOutput;
    }
    return _output;
}

#pragma mark - AVCaptureVideoDataOutputSampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    CVPixelBufferRef buffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CMTime timeStamp = CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
    id<ZGCaptureDeviceDataOutputPixelBufferDelegate> delegate = self.delegate;
    if (delegate && [delegate respondsToSelector:@selector(captureDevice:didCapturedData:presentationTimeStamp:)]) {
        [delegate captureDevice:self didCapturedData:buffer presentationTimeStamp:timeStamp];
    }
}

@end

#endif // _Module_CustomVideoCapture
