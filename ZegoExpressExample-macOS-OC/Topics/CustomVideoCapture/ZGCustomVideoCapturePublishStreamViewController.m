//
//  ZGCustomVideoCapturePublishStreamViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/20.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_CustomVideoCapture

#import "ZGCustomVideoCapturePublishStreamViewController.h"
#import "ZGAppGlobalConfigManager.h"
#import "ZGUserIDHelper.h"
#import "ZGCaptureDeviceCamera.h"
#import "ZGCaptureDeviceImage.h"
#import <ZegoExpressEngine/ZegoExpressEngine.h>

NSString* const ZGCustomVideoCapturePublishStreamKeyRoomID = @"kRoomID";
NSString* const ZGCustomVideoCapturePublishStreamKeyStreamID = @"kStreamID";

@interface ZGCustomVideoCapturePublishStreamViewController () <ZegoEventHandler, ZegoCustomVideoCaptureHandler, ZGCaptureDeviceDataOutputPixelBufferDelegate>

@property (unsafe_unretained) IBOutlet NSTextView *logView;

@property (weak) IBOutlet NSImageView *previewView;
@property (strong) ZegoCanvas *previewCanvas;

@property (weak) IBOutlet NSTextField *roomIDTextField;
@property (weak) IBOutlet NSTextField *streamIDTextField;
@property (weak) IBOutlet NSButton *startButton;
@property (weak) IBOutlet NSButton *stopButton;

@property (weak) IBOutlet NSPopUpButton *captureSourcePopUpButton;
@property (weak) IBOutlet NSPopUpButton *dataFormatPopUpButton;

@property (copy) NSString *roomID;
@property (copy) NSString *streamID;

@property (nonatomic, strong) id<ZGCaptureDevice> captureDevice;

/// Capture source type, 0: Camera, 1: Motion Image
@property (nonatomic, assign) NSUInteger captureSourceType;

/// Capture CVPixelBuffer data format, 0: BGRA32, 1: NV12(yuv420sp)
@property (nonatomic, assign) NSUInteger captureDataFormat;


@property (strong) ZegoExpressEngine *engine;

@end

@implementation ZGCustomVideoCapturePublishStreamViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupUI];
    [self createEngine];
}

- (void)setupUI {
    self.title = @"Custom Video Capture";
    
    self.dataFormatPopUpButton.autoenablesItems = NO;
    
    self.startButton.enabled = YES;
    self.stopButton.enabled = NO;
        
    self.roomID = [self savedValueForKey:ZGCustomVideoCapturePublishStreamKeyRoomID] ? : @"";
    self.roomIDTextField.stringValue = self.roomID;
    
    self.streamID = [self savedValueForKey:ZGCustomVideoCapturePublishStreamKeyStreamID] ? : @"";
    self.streamIDTextField.stringValue = self.streamID;
}

- (void)createEngine {
    // Set capture config
    ZegoCustomVideoCaptureConfig *captureConfig = [[ZegoCustomVideoCaptureConfig alloc] init];
    captureConfig.bufferType = ZegoVideoBufferTypeCVPixelBuffer;
    
    ZegoEngineConfig *engineConfig = [[ZegoEngineConfig alloc] init];
    engineConfig.customVideoCaptureMainConfig = captureConfig;
    
    // Set engine config, must be called before create engine
    [ZegoExpressEngine setEngineConfig:engineConfig];
    
    ZGAppGlobalConfig *appConfig = [[ZGAppGlobalConfigManager sharedManager] globalConfig];

    [self appendLog:@" 🚀 Create ZegoExpressEngine"];

    self.engine = [ZegoExpressEngine createEngineWithAppID:(unsigned int)appConfig.appID appSign:appConfig.appSign isTestEnv:appConfig.isTestEnv scenario:appConfig.scenario eventHandler:self];
    
    // Set custom video capture handler
    [[ZegoExpressEngine sharedEngine] setCustomVideoCaptureHandler:self];
    
    ZegoVideoConfig *videoConfig = [ZegoVideoConfig configWithPreset:ZegoVideoConfigPreset1080P];
    [[ZegoExpressEngine sharedEngine] setVideoConfig:videoConfig];
}

#pragma mark - Start and Stop

- (IBAction)startButtonClick:(NSButton *)sender {
    self.roomIDTextField.enabled = NO;
    self.streamIDTextField.enabled = NO;
    self.captureSourcePopUpButton.enabled = NO;
    self.dataFormatPopUpButton.enabled = NO;
    self.startButton.enabled = NO;
    self.stopButton.enabled = YES;
    
    self.captureDevice = nil;
    
    self.roomID = self.roomIDTextField.stringValue;
    self.streamID = self.streamIDTextField.stringValue;
    
    [self saveValue:self.roomID forKey:ZGCustomVideoCapturePublishStreamKeyRoomID];
    [self saveValue:self.streamID forKey:ZGCustomVideoCapturePublishStreamKeyStreamID];
    
    NSString *userID = ZGUserIDHelper.userID;
    NSString *userName = ZGUserIDHelper.userName;
    
    // Login room
    [self appendLog:[NSString stringWithFormat:@" 🚪 Start login room, roomID: %@", self.roomID]];
    [self.engine loginRoom:self.roomID user:[ZegoUser userWithUserID:userID userName:userName]];
    
    // When custom video capture is enabled, developers need to render the preview by themselves
//    [self.engine startPreview:self.previewCanvas];
    
    // Start publishing
    [self appendLog:[NSString stringWithFormat:@" 📤 Start publishing stream, streamID: %@", self.streamID]];
    [self.engine startPublishingStream:self.streamID];
}

- (IBAction)stopButtonClick:(NSButton *)sender {
    self.roomIDTextField.enabled = YES;
    self.streamIDTextField.enabled = YES;
    self.captureSourcePopUpButton.enabled = YES;
    self.dataFormatPopUpButton.enabled = YES;
    self.startButton.enabled = YES;
    self.stopButton.enabled = NO;
    
    // Stop publishing
    [self appendLog:@" 📤 Stop publishing stream"];
    [self.engine stopPublishingStream];
    
    // Logout room
    [self appendLog:@" 🚪 Logout room"];
    [self.engine logoutRoom:self.roomID];
}

#pragma mark - Exit

- (void)dealloc {
    ZGLogInfo(@" 🏳️ Destroy ZegoExpressEngine");
    [ZegoExpressEngine destroyEngine:^{
        // This callback is only used to notify the completion of the release of internal resources of the engine.
        // Developers cannot release resources related to the engine within this callback.
        //
        // In general, developers do not need to listen to this callback.
        ZGLogInfo(@" 🚩 🏳️ Destroy ZegoExpressEngine complete");
    }];
    
    // After destroying the engine, you will not receive the `-onStop:` callback, you need to stop the custom video caputre manually.
    [self.captureDevice stopCapture];
    
    // In order not to affect other example topics, restore the default engine configuration.
    [ZegoExpressEngine setEngineConfig:[[ZegoEngineConfig alloc] init]];
}

#pragma mark - Actions

- (IBAction)captureSourcePopUpButtonAction:(NSPopUpButton *)sender {
    self.captureSourceType = sender.indexOfSelectedItem;
    
    if (self.captureSourceType == 1) {
        [[self.dataFormatPopUpButton itemAtIndex:1] setEnabled:NO];
        [self.dataFormatPopUpButton selectItemAtIndex:0];
    } else {
        [[self.dataFormatPopUpButton itemAtIndex:1] setEnabled:YES];
        [self.dataFormatPopUpButton selectItemAtIndex:0];
    }
}

- (IBAction)dataFormatPopUpButtonAction:(NSPopUpButton *)sender {
    self.captureDataFormat = sender.indexOfSelectedItem;
}

#pragma mark - Getter

- (id<ZGCaptureDevice>)captureDevice {
    if (!_captureDevice) {
        if (self.captureSourceType == 0) {
            // BGRA32 or NV12
            OSType pixelFormat = self.captureDataFormat == 0 ? kCVPixelFormatType_32BGRA : kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange;
            _captureDevice = [[ZGCaptureDeviceCamera alloc] initWithPixelFormatType:pixelFormat];
            _captureDevice.delegate = self;
        } else if (self.captureSourceType == 1) {
            _captureDevice = [[ZGCaptureDeviceImage alloc] initWithMotionImage:[NSImage imageNamed:@"ZegoLogo"]];
            _captureDevice.delegate = self;
        }
    }
    return _captureDevice;
}

#pragma mark - ZegoCustomVideoCaptureHandler

// Note: This callback is not in the main thread. If you have UI operations, please switch to the main thread yourself.
- (void)onStart:(ZegoPublishChannel)channel {
    [self appendLog:[NSString stringWithFormat:@" 🚩 🟢 ZegoCustomVideoCaptureHandler onStart, channel: %d", (int)channel]];
    [self.captureDevice startCapture];
}

// Note: This callback is not in the main thread. If you have UI operations, please switch to the main thread yourself.
- (void)onStop:(ZegoPublishChannel)channel {
    [self appendLog:[NSString stringWithFormat:@" 🚩 🔴 ZegoCustomVideoCaptureHandler onStop, channel: %d", (int)channel]];
    [self.captureDevice stopCapture];
}


#pragma mark - ZGCustomVideoCapturePixelBufferDelegate

- (void)captureDevice:(nonnull id<ZGCaptureDevice>)device didCapturedData:(nonnull CVPixelBufferRef)data presentationTimeStamp:(CMTime)timeStamp {
    
    // Send pixel buffer to ZEGO SDK
    [[ZegoExpressEngine sharedEngine] sendCustomVideoCapturePixelBuffer:data timeStamp:timeStamp];
    
    // When custom video capture is enabled, developers need to render the preview by themselves
    [self renderWithCVPixelBuffer:data];
}

#pragma mark - Render Preview

- (void)renderWithCVPixelBuffer:(CVPixelBufferRef)buffer {
    CIImage *image = [CIImage imageWithCVPixelBuffer:buffer];
    NSCIImageRep *rep = [NSCIImageRep imageRepWithCIImage:image];
    NSImage *nsImage = [[NSImage alloc] initWithSize:rep.size];
    [nsImage addRepresentation:rep];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.previewView.image = nsImage;
    });
}

#pragma mark - Helper Methods

/// Append Log to Top View
- (void)appendLog:(NSString *)tipText {
    if (!tipText || tipText.length == 0) {
        return;
    }
    ZGLogInfo(@"%@", tipText);
    
    NSString *oldText = self.logView.string;
    NSString *newLine = oldText.length == 0 ? @"" : @"\n";
    NSString *newText = [NSString stringWithFormat:@"%@%@%@", oldText, newLine, tipText];
    
    self.logView.string = newText;
    [self.logView scrollToEndOfDocument:nil];
}


@end

#endif // _Module_CustomVideoCapture
