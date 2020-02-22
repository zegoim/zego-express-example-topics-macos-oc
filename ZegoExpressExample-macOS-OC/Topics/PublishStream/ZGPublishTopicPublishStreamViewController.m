//
//  ZGPublishTopicPublishStreamViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/19.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_Publish

#import "ZGPublishTopicPublishStreamViewController.h"
#import "ZGAppGlobalConfigManager.h"
#import "ZGUserIDHelper.h"
#import <ZegoExpressEngine/ZegoExpressEngine.h>

NSString* const ZGPublishTopicPublishStreamKeyRoomID = @"kRoomID";
NSString* const ZGPublishTopicPublishStreamKeyStreamID = @"kStreamID";

@interface ZGPublishTopicPublishStreamViewController () <ZegoEventHandler>

@property (unsafe_unretained) IBOutlet NSTextView *logView;
@property (weak) IBOutlet NSView *previewView;
@property (strong) ZegoCanvas *previewCanvas;

@property (weak) IBOutlet NSTextField *publishResolutionLabel;
@property (weak) IBOutlet NSTextField *publishQualityLabel;
@property (weak) IBOutlet NSTextField *roomIDTextField;
@property (weak) IBOutlet NSTextField *streamIDTextField;
@property (weak) IBOutlet NSButton *startButton;
@property (weak) IBOutlet NSButton *stopButton;
@property (weak) IBOutlet NSButton *microphoneCheckBox;
@property (weak) IBOutlet NSButton *audioOutputCheckBox;
@property (weak) IBOutlet NSButton *cameraCheckBox;
@property (weak) IBOutlet NSButton *hardwareEncoderCheckBox;
@property (weak) IBOutlet NSPopUpButton *resolutionPopUpButton;
@property (weak) IBOutlet NSPopUpButton *fpsPopUpButton;
@property (weak) IBOutlet NSPopUpButton *BitratePopUpButton;
@property (weak) IBOutlet NSPopUpButton *viewModePopUpButton;
@property (weak) IBOutlet NSPopUpButton *mirrorModePopUpButton;
@property (weak) IBOutlet NSPopUpButton *audioConfigPopUpButton;
@property (weak) IBOutlet NSTextField *streamExtraInfoTextField;
@property (weak) IBOutlet NSButton *setStreamExtraInfoButton;

@property (copy) NSString *roomID;
@property (copy) NSString *streamID;

@property (strong) ZegoVideoConfig *videoConfig;

@property (assign) ZegoViewMode previewViewMode;
@property (assign) ZegoVideoMirrorMode videoMirrorMode;

@property (copy) NSString *streamExtraInfo;

@property (assign) ZegoRoomState roomState;
@property (assign) ZegoPublisherState publisherState;

@property (strong) ZegoExpressEngine *engine;

@end

@implementation ZGPublishTopicPublishStreamViewController

#pragma mark - Setup

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupUI];
    [self createEngine];
}

- (void)setupUI {
    self.title = @"Publish Stream";
    
    self.publishResolutionLabel.stringValue = @"Resolution: ";
    self.publishResolutionLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.4];
    self.publishResolutionLabel.drawsBackground = YES;
    self.publishResolutionLabel.textColor = [NSColor whiteColor];
    
    self.publishQualityLabel.stringValue = @"Quality: ";
    self.publishQualityLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.4];
    self.publishQualityLabel.drawsBackground = YES;
    self.publishQualityLabel.textColor = [NSColor whiteColor];
    
    self.roomID = [self savedValueForKey:ZGPublishTopicPublishStreamKeyRoomID] ? : @"";
    self.roomIDTextField.stringValue = self.roomID;
    
    self.streamID = [self savedValueForKey:ZGPublishTopicPublishStreamKeyStreamID] ? : @"";
    self.streamIDTextField.stringValue = self.streamID;
}

- (void)createEngine {
    ZGAppGlobalConfig *appConfig = [[ZGAppGlobalConfigManager sharedManager] globalConfig];
    
    [self appendLog:@" 🚀 Create ZegoExpressEngine"];

    self.engine = [ZegoExpressEngine createEngineWithAppID:(unsigned int)appConfig.appID appSign:appConfig.appSign isTestEnv:appConfig.isTestEnv scenario:appConfig.scenario eventHandler:self];
    
    // Setup
    [self.engine muteMicrophone:NO];
    [self.engine muteAudioOutput:NO];
    [self.engine enableCamera:YES];
    [self.engine enableHardwareEncoder:NO];
    
    self.videoConfig = [[ZegoVideoConfig alloc] init];
    self.videoConfig.captureResolution = CGSizeMake(1920, 1080);
    self.videoConfig.encodeResolution = CGSizeMake(1920, 1080);
    self.videoConfig.fps = 30;
    self.videoConfig.bitrate = 3000000;
    [self.engine setVideoConfig:self.videoConfig];
    
    self.previewViewMode = ZegoViewModeAspectFit;
    
    self.videoMirrorMode = ZegoVideoMirrorModeOnlyPreviewMirror;
    [self.engine setVideoMirrorMode:self.videoMirrorMode];
    
    [self.engine setAudioConfig:[ZegoAudioConfig configWithPreset:ZegoAudioConfigPresetLowLatencyStandardQuality]];
    
    // Start preview
    self.previewCanvas = [ZegoCanvas canvasWithView:self.previewView];
    self.previewCanvas.viewMode = self.previewViewMode;
    
    [self appendLog:@" 🔌 Start preview"];
    [self.engine startPreview:self.previewCanvas];
}

#pragma mark - Start and Stop

- (IBAction)startButtonClick:(NSButton *)sender {
    self.roomID = self.roomIDTextField.stringValue;
    self.streamID = self.streamIDTextField.stringValue;
    
    [self saveValue:self.roomID forKey:ZGPublishTopicPublishStreamKeyRoomID];
    [self saveValue:self.streamID forKey:ZGPublishTopicPublishStreamKeyStreamID];
    
    NSString *userID = ZGUserIDHelper.userID;
    NSString *userName = ZGUserIDHelper.userName;
    
    // Login room
    [self appendLog:[NSString stringWithFormat:@" 🚪 Start login room, roomID: %@", self.roomID]];
    [self.engine loginRoom:self.roomID user:[ZegoUser userWithUserID:userID userName:userName] config:nil];
    
    // Start publishing
    [self appendLog:[NSString stringWithFormat:@" 📤 Start publishing stream, streamID: %@", self.streamID]];
    [self.engine startPublishing:self.streamID];
}

- (IBAction)stopButtonClick:(NSButton *)sender {
    // Stop publishing
    [self appendLog:@" 📤 Stop publishing stream"];
    [self.engine stopPublishing];
    
    // Logout room
    [self appendLog:@" 🚪 Logout room"];
    [self.engine logoutRoom:self.roomID];
    
    self.publishResolutionLabel.stringValue = @"Resolution: ";
    self.publishQualityLabel.stringValue = @"Quality: ";
}

#pragma mark - Exit

- (void)viewDidDisappear {
    // It is recommended to logout room when stopping the video call.
    [self appendLog:[NSString stringWithFormat:@" 🚪 Logout room, roomID: %@", self.roomID]];
    [self.engine logoutRoom:self.roomID];
    
    // And you can destroy the engine when there is no need to call.
    [self appendLog:@" 🏳️ Destroy ZegoExpressEngine"];
    [ZegoExpressEngine destroyEngine];
}

#pragma mark - Actions

- (IBAction)microphoneCheckBoxClick:(NSButton *)sender {
    [self appendLog:[NSString stringWithFormat:@" %@ microphone", sender.state == NSControlStateValueOn ? @" 🎙 Enable" : @" 🙊 Mute"]];
    
    [self.engine muteMicrophone:sender.state == NSControlStateValueOn ? NO : YES];
}

- (IBAction)audioOutputCheckBoxClick:(NSButton *)sender {
    [self appendLog:[NSString stringWithFormat:@" %@ audio output", sender.state == NSControlStateValueOn ? @" 🔊 Enable" : @" 🔇 Mute"]];
    
    [self.engine muteAudioOutput:sender.state == NSControlStateValueOn ? NO : YES];
}

- (IBAction)cameraCheckBoxClick:(NSButton *)sender {
    [self appendLog:[NSString stringWithFormat:@" %@ camera", sender.state == NSControlStateValueOn ? @" 📸 Enable" : @" 📷 Disable"]];
    
    [self.engine enableCamera:sender.state == NSControlStateValueOn ? YES : NO];
}

- (IBAction)hardwareEncoderCheckBoxClick:(NSButton *)sender {
    
    if (self.publisherState != ZegoPublisherStateNoPublish) {
        [self appendLog:@" ❗️ Switch hardware encoder will not take effect until the next publish"];
    }
    
    [self appendLog:[NSString stringWithFormat:@" %@ hardware encoder", sender.state == NSControlStateValueOn ? @" ⚙️ Enable" : @" ⚙️ Disable"]];
    [self.engine enableHardwareEncoder:sender.state == NSControlStateValueOn ? YES : NO];
}

- (IBAction)resolutionPopUpButtonAction:(NSPopUpButton *)sender {
    CGSize resolution = self.videoConfig.captureResolution;
    switch (sender.indexOfSelectedItem) {
        case 0:
            resolution = CGSizeMake(320, 180);
            break;
        case 1:
            resolution = CGSizeMake(480, 270);
            break;
        case 2:
            resolution = CGSizeMake(640, 360);
            break;
        case 3:
            resolution = CGSizeMake(960, 540);
            break;
        case 4:
            resolution = CGSizeMake(1280, 720);
            break;
        case 5:
            resolution = CGSizeMake(1920, 1080);
            break;
        default:
            break;
    }
    self.videoConfig.captureResolution = resolution;
    self.videoConfig.encodeResolution = resolution;
    
    [self appendLog:[NSString stringWithFormat:@" 🖼 Resolution changed to: %d x %d", (int)resolution.width, (int)resolution.height]];
    [self.engine setVideoConfig:self.videoConfig];
}

- (IBAction)fpsPopUpButtonAction:(NSPopUpButton *)sender {
    int fps = self.videoConfig.fps;
    switch (sender.indexOfSelectedItem) {
        case 0:
            fps = 5;
            break;
        case 1:
            fps = 10;
            break;
        case 2:
            fps = 15;
            break;
        case 3:
            fps = 20;
            break;
        case 4:
            fps = 25;
            break;
        case 5:
            fps = 30;
            break;
        default:
            break;
    }
    self.videoConfig.fps = fps;
    
    [self appendLog:[NSString stringWithFormat:@" 📽 FPS changed to: %d", fps]];
    [self.engine setVideoConfig:self.videoConfig];
}

- (IBAction)bitratePopUpButtonAction:(NSPopUpButton *)sender {
    int bitrate = self.videoConfig.bitrate;
    switch (sender.indexOfSelectedItem) {
        case 0:
            bitrate = 300000;
            break;
        case 1:
            bitrate = 400000;
            break;
        case 2:
            bitrate = 600000;
            break;
        case 3:
            bitrate = 1200000;
            break;
        case 4:
            bitrate = 1500000;
            break;
        case 5:
            bitrate = 3000000;
            break;
        default:
            break;
    }
    self.videoConfig.bitrate = bitrate;
    
    [self appendLog:[NSString stringWithFormat:@" 🎛 Bitrate changed to: %d", bitrate]];
    [self.engine setVideoConfig:self.videoConfig];
}

- (IBAction)viewModePopUpButtonAction:(NSPopUpButton *)sender {
    NSString *previewModeString;
    switch (sender.indexOfSelectedItem) {
        case 0:
            previewModeString = @"AspectFit";
            self.previewViewMode = ZegoViewModeAspectFit;
            break;
        case 1:
            previewModeString = @"AspectFill";
            self.previewViewMode = ZegoViewModeAspectFill;
            break;
        case 2:
            previewModeString = @"ScaleToFill";
            self.previewViewMode = ZegoViewModeScaleToFill;
            break;
        default:
            break;
    }
    
    [self appendLog:[NSString stringWithFormat:@" 🖼 View mode changed to: %@", previewModeString]];
    self.previewCanvas.viewMode = self.previewViewMode;
    [self.engine startPreview:self.previewCanvas];
}

- (IBAction)mirrorModePopUpButtonAction:(NSPopUpButton *)sender {
    NSString *mirrorModeString;
    switch (sender.indexOfSelectedItem) {
        case 0:
            mirrorModeString = @"OnlyPreviewMirror";
            self.videoMirrorMode = ZegoVideoMirrorModeOnlyPreviewMirror;
            break;
        case 1:
            mirrorModeString = @"BothMirror";
            self.videoMirrorMode = ZegoVideoMirrorModeBothMirror;
            break;
        case 2:
            mirrorModeString = @"NoMirror";
            self.videoMirrorMode = ZegoVideoMirrorModeNoMirror;
            break;
        case 3:
            mirrorModeString = @"OnlyPublishMirror";
            self.videoMirrorMode = ZegoVideoMirrorModeOnlyPublishMirror;
            break;
        default:
            break;
    }
    
    [self appendLog:[NSString stringWithFormat:@" 🤳 Mirror mode changed to: %@", mirrorModeString]];
    [self.engine setVideoMirrorMode:self.videoMirrorMode];
}

- (IBAction)audioConfigPopUpButtonAction:(NSPopUpButton *)sender {
    // TODO: AudioConfig
}

- (IBAction)setStreamExtraInfoButtonClick:(NSButton *)sender {
    self.streamExtraInfo = self.streamExtraInfoTextField.stringValue;
    [self appendLog:[NSString stringWithFormat:@" 💬 Set stream extra info: %@", self.streamExtraInfo]];
    
    __weak typeof(self) weakSelf = self;
    [self.engine setStreamExtraInfo:self.streamExtraInfo callback:^(int errorCode) {
        __strong typeof(self) strongSelf = weakSelf;
        [strongSelf appendLog:[NSString stringWithFormat:@" 🚩 💬 Set stream extra info result: %d", errorCode]];
    }];
}

#pragma mark - ZegoEventHandler Room Event

- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode room:(NSString *)roomID {
    if (errorCode != 0) {
        [self appendLog:[NSString stringWithFormat:@" 🚩 ❌ 🚪 Room state error, errorCode: %d", errorCode]];
    } else {
        if (state == ZegoRoomStateConnected) {
            [self appendLog:@" 🚩 🚪 Login room success"];
        } else if (state == ZegoRoomStateConnecting) {
            [self appendLog:@" 🚩 🚪 Requesting login room"];
        } else if (state == ZegoRoomStateDisconnected) {
            [self appendLog:@" 🚩 🚪 Logout room"];
            
            // After logout room, the preview will stop. You need to re-start preview.
            [self.engine startPreview:self.previewCanvas];
        }
    }
    self.roomState = state;
}

#pragma mark - ZegoEventHandler Publish Event

- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode stream:(NSString *)streamID {
    if (errorCode != 0) {
        [self appendLog:[NSString stringWithFormat:@" 🚩 ❌ 📤 Publishing stream error of streamID: %@, errorCode:%d", streamID, errorCode]];
    } else {
        if (state == ZegoPublisherStatePublishing) {
            [self appendLog:@" 🚩 📤 Publishing stream"];
        } else if (state == ZegoPublisherStatePublishRequesting) {
            [self appendLog:@" 🚩 📤 Requesting publish stream"];
        } else if (state == ZegoPublisherStateNoPublish) {
            [self appendLog:@" 🚩 📤 Stop playing stream"];
        }
    }
    self.publisherState = state;
}

- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality stream:(NSString *)streamID {
    NSString *networkQuality = @"";
    switch (quality.level) {
        case 0:
            networkQuality = @"☀️";
            break;
        case 1:
            networkQuality = @"⛅️";
            break;
        case 2:
            networkQuality = @"☁️";
            break;
        case 3:
            networkQuality = @"🌧";
            break;
        case 4:
            networkQuality = @"❌";
            break;
        default:
            break;
    }
    NSMutableString *text = [NSMutableString string];
    [text appendFormat:@"FPS: %d fps \n", (int)quality.videoSendFPS];
    [text appendFormat:@"Bitrate: %.2f kb/s \n", quality.videoKBPS];
    [text appendFormat:@"HardwareEncode: %@ \n", quality.isHardwareEncode ? @"✅" : @"❎"];
    [text appendFormat:@"NetworkQuality: %@", networkQuality];
    self.publishQualityLabel.stringValue = [text copy];
}

- (void)onPublisherVideoSizeChanged:(CGSize)size {
    self.publishResolutionLabel.stringValue = [NSString stringWithFormat:@"Resolution: %d x %d", (int)size.width, (int)size.height];
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

#endif // _Module_Publish
