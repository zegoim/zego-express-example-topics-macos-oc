//
//  ZGPlayTopicPlayStreamViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/20.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_Play

#import "ZGPlayTopicPlayStreamViewController.h"
#import "ZGAppGlobalConfigManager.h"
#import "ZGUserIDHelper.h"
#import <ZegoExpressEngine/ZegoExpressEngine.h>

NSString* const ZGPlayTopicPlayStreamKeyRoomID = @"kRoomID";
NSString* const ZGPlayTopicPlayStreamKeyStreamID = @"kStreamID";


@interface ZGPlayTopicPlayStreamViewController () <ZegoEventHandler>

@property (unsafe_unretained) IBOutlet NSTextView *logView;
@property (weak) IBOutlet NSView *playView;
@property (strong) ZegoCanvas *playCanvas;

@property (weak) IBOutlet NSTextField *playResolutionLabel;
@property (weak) IBOutlet NSTextField *playQualityLabel;
@property (weak) IBOutlet NSTextField *playStreamExtraInfoLabel;

@property (weak) IBOutlet NSTextField *roomIDTextField;
@property (weak) IBOutlet NSTextField *streamIDTextField;

@property (weak) IBOutlet NSButton *startButton;
@property (weak) IBOutlet NSButton *stopButton;

@property (weak) IBOutlet NSButton *speakerCheckBox;
@property (weak) IBOutlet NSButton *hardwareDecoderCheckBox;
@property (weak) IBOutlet NSPopUpButton *viewModePopUpButton;

@property (copy) NSString *roomID;
@property (copy) NSString *streamID;

@property (strong) ZegoVideoConfig *videoConfig;

@property (assign) ZegoViewMode playViewMode;

@property (assign) ZegoRoomState roomState;
@property (assign) ZegoPlayerState playerState;

@end

@implementation ZGPlayTopicPlayStreamViewController

#pragma mark - Setup

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupUI];
    [self createEngine];
}

- (void)setupUI {
    self.title = @"Play Stream";
    
    self.startButton.enabled = YES;
    self.stopButton.enabled = NO;
    
    self.playResolutionLabel.stringValue = @"Resolution: ";
    self.playResolutionLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.4];
    self.playResolutionLabel.drawsBackground = YES;
    self.playResolutionLabel.textColor = [NSColor whiteColor];
    
    self.playQualityLabel.stringValue = @"Quality: ";
    self.playQualityLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.4];
    self.playQualityLabel.drawsBackground = YES;
    self.playQualityLabel.textColor = [NSColor whiteColor];
    
    self.playStreamExtraInfoLabel.stringValue = @"Stream Extra Info: ";
    self.playStreamExtraInfoLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.4];
    self.playStreamExtraInfoLabel.drawsBackground = YES;
    self.playStreamExtraInfoLabel.textColor = [NSColor whiteColor];
    
    self.roomID = [self savedValueForKey:ZGPlayTopicPlayStreamKeyRoomID] ? : @"";
    self.roomIDTextField.stringValue = self.roomID;
    
    self.streamID = [self savedValueForKey:ZGPlayTopicPlayStreamKeyStreamID] ? : @"";
    self.streamIDTextField.stringValue = self.streamID;
}

- (void)createEngine {
    ZGAppGlobalConfig *appConfig = [[ZGAppGlobalConfigManager sharedManager] globalConfig];
    
    [self appendLog:@" 🚀 Create ZegoExpressEngine"];

    [ZegoExpressEngine createEngineWithAppID:(unsigned int)appConfig.appID appSign:appConfig.appSign isTestEnv:appConfig.isTestEnv scenario:appConfig.scenario eventHandler:self];
    
    // Setup
    [[ZegoExpressEngine sharedEngine] muteSpeaker:NO];
    [[ZegoExpressEngine sharedEngine] enableHardwareDecoder:NO];
    
    self.playViewMode = ZegoViewModeAspectFit;
    self.playCanvas = [ZegoCanvas canvasWithView:self.playView];
    self.playCanvas.viewMode = self.playViewMode;
}

#pragma mark - Start and Stop

- (IBAction)startButtonClick:(NSButton *)sender {
    self.roomIDTextField.enabled = NO;
    self.streamIDTextField.enabled = NO;
    self.hardwareDecoderCheckBox.enabled = NO;
    self.startButton.enabled = NO;
    self.stopButton.enabled = YES;
    
    self.roomID = self.roomIDTextField.stringValue;
    self.streamID = self.streamIDTextField.stringValue;
    
    [self saveValue:self.roomID forKey:ZGPlayTopicPlayStreamKeyRoomID];
    [self saveValue:self.streamID forKey:ZGPlayTopicPlayStreamKeyStreamID];
    
    NSString *userID = ZGUserIDHelper.userID;
    NSString *userName = ZGUserIDHelper.userName;
    
    // Login room
    [self appendLog:[NSString stringWithFormat:@" 🚪 Start login room, roomID: %@", self.roomID]];
    [[ZegoExpressEngine sharedEngine] loginRoom:self.roomID user:[ZegoUser userWithUserID:userID userName:userName]];
    
    // Start publishing
    [self appendLog:@" 📥 Strat playing stream"];
    [[ZegoExpressEngine sharedEngine] startPlayingStream:self.streamID canvas:self.playCanvas];
}

- (IBAction)stopButtonClick:(NSButton *)sender {
    self.roomIDTextField.enabled = YES;
    self.streamIDTextField.enabled = YES;
    self.hardwareDecoderCheckBox.enabled = YES;
    self.startButton.enabled = YES;
    self.stopButton.enabled = NO;
    
    // Stop publishing
    [self appendLog:@" 📥 Stop playing stream"];
    [[ZegoExpressEngine sharedEngine] stopPlayingStream:self.streamID];
    
    // Logout room
    [self appendLog:@" 🚪 Logout room"];
    [[ZegoExpressEngine sharedEngine] logoutRoom:self.roomID];
    
    self.playResolutionLabel.stringValue = @"Resolution: ";
    self.playQualityLabel.stringValue = @"Quality: ";
    self.playStreamExtraInfoLabel.stringValue = @"Stream Extra Info: ";
}

#pragma mark - Exit

- (void)viewDidDisappear {
    // Stop playing before exiting
    if (self.playerState != ZegoPlayerStateNoPlay) {
        [self appendLog:@" 📥 Stop playing stream"];
        [[ZegoExpressEngine sharedEngine] stopPlayingStream:self.streamID];
    }
    
    // Logout room before exiting
    if (self.roomState != ZegoRoomStateDisconnected) {
        [self appendLog:@" 🚪 Logout room"];
        [[ZegoExpressEngine sharedEngine] logoutRoom:self.roomID];
    }
    
    // Can destroy the engine when you don't need audio and video calls
    [self appendLog:@" 🏳️ Destroy ZegoExpressEngine"];
    [ZegoExpressEngine destroyEngine:nil];
}

#pragma mark - Actions

- (IBAction)speakerCheckBoxClick:(NSButton *)sender {
    [self appendLog:[NSString stringWithFormat:@" %@ speaker", sender.state == NSControlStateValueOn ? @" 🔊 Enable" : @" 🔇 Mute"]];
    
    [[ZegoExpressEngine sharedEngine] muteSpeaker:sender.state == NSControlStateValueOn ? NO : YES];
}

- (IBAction)hardwareDecoderCheckBoxClick:(NSButton *)sender {
    
    if (self.playerState != ZegoPublisherStateNoPublish) {
        [self appendLog:@" ❗️ Switch hardware decoder will not take effect until the next publish"];
    }
    
    [self appendLog:[NSString stringWithFormat:@" %@ hardware decoder", sender.state == NSControlStateValueOn ? @" ⚙️ Enable" : @" ⚙️ Disable"]];
    [[ZegoExpressEngine sharedEngine] enableHardwareDecoder:sender.state == NSControlStateValueOn ? YES : NO];
}

- (IBAction)playVolumeSliderValueChanged:(NSSlider *)sender {
    if (self.playerState != ZegoPlayerStatePlaying) {
        [self appendLog:@" ❗️ You must play stream before changing the stream volume"];
        return;
    }
    
    [self appendLog:[NSString stringWithFormat:@" 🔊 Stream volume changed to: %d", sender.intValue]];
    [[ZegoExpressEngine sharedEngine] setPlayVolume:sender.intValue streamID:self.streamID];
}

- (IBAction)viewModePopUpButtonAction:(NSPopUpButton *)sender {
    NSString *playViewModeString;
    switch (sender.indexOfSelectedItem) {
        case 0:
            playViewModeString = @"AspectFit";
            self.playViewMode = ZegoViewModeAspectFit;
            break;
        case 1:
            playViewModeString = @"AspectFill";
            self.playViewMode = ZegoViewModeAspectFill;
            break;
        case 2:
            playViewModeString = @"ScaleToFill";
            self.playViewMode = ZegoViewModeScaleToFill;
            break;
        default:
            break;
    }
    
    [self appendLog:[NSString stringWithFormat:@" 🖼 View mode changed to: %@", playViewModeString]];
    self.playCanvas.viewMode = self.playViewMode;
    [[ZegoExpressEngine sharedEngine] startPlayingStream:self.streamID canvas:self.playCanvas];
}

#pragma mark - ZegoEventHandler Room Event

- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode extendedData:(NSDictionary *)extendedData roomID:(NSString *)roomID {
    if (errorCode != 0) {
        [self appendLog:[NSString stringWithFormat:@" 🚩 ❌ 🚪 Room state error, errorCode: %d", errorCode]];
    } else {
        if (state == ZegoRoomStateConnected) {
            [self appendLog:@" 🚩 🚪 Login room success"];
        } else if (state == ZegoRoomStateConnecting) {
            [self appendLog:@" 🚩 🚪 Requesting login room"];
        } else if (state == ZegoRoomStateDisconnected) {
            [self appendLog:@" 🚩 🚪 Logout room"];
        }
    }
    self.roomState = state;
}

- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList extendedData:(NSDictionary *)extendedData roomID:(NSString *)roomID {
    for (ZegoStream *stream in streamList) {
        if ([stream.streamID isEqualToString:self.streamID]) {
            self.playStreamExtraInfoLabel.stringValue = [NSString stringWithFormat:@"Stream Extra Info: %@", stream.extraInfo];
            [self appendLog:[NSString stringWithFormat:@" 🚩 💬 Stream Extra Info First Recv: %@, StreamID: %@", stream.extraInfo, stream.streamID]];
        }
    }
}

- (void)onRoomStreamExtraInfoUpdate:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID {
    for (ZegoStream *stream in streamList) {
        if ([stream.streamID isEqualToString:self.streamID]) {
            self.playStreamExtraInfoLabel.stringValue = [NSString stringWithFormat:@"Stream Extra Info: %@", stream.extraInfo];
            [self appendLog:[NSString stringWithFormat:@" 🚩 💬 Stream Extra Info Update: %@, StreamID: %@", stream.extraInfo, stream.streamID]];
        }
    }
}

#pragma mark - ZegoEventHandler Publish Event

- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode extendedData:(NSDictionary *)extendedData streamID:(NSString *)streamID {
    if (![streamID isEqualToString:self.streamID]) {
        return;
    }
    
    if (errorCode != 0) {
        [self appendLog:[NSString stringWithFormat:@" 🚩 ❌ 📥 Playing stream error of streamID: %@, errorCode:%d", streamID, errorCode]];
    } else {
        if (state == ZegoPlayerStatePlaying) {
            [self appendLog:@" 🚩 📥 Playing stream"];
        } else if (state == ZegoPlayerStatePlayRequesting) {
            [self appendLog:@" 🚩 📥 Requesting play stream"];
        } else if (state == ZegoPlayerStateNoPlay) {
            [self appendLog:@" 🚩 📥 Stop playing stream"];
        }
    }
    self.playerState = state;
}

- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality streamID:(NSString *)streamID {
    if (![streamID isEqualToString:self.streamID]) {
        return;
    }
    
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
    [text appendFormat:@"FPS: %d fps\n", (int)quality.videoRecvFPS];
    [text appendFormat:@"Bitrate: %.2f kb/s \n", quality.videoKBPS];
    [text appendFormat:@"HardwareDecode: %@ \n", quality.isHardwareDecode ? @"✅" : @"❎"];
    [text appendFormat:@"NetworkQuality: %@", networkQuality];
    self.playQualityLabel.stringValue = [text copy];
}

- (void)onPlayerVideoSizeChanged:(CGSize)size streamID:(NSString *)streamID {
    if (![streamID isEqualToString:self.streamID]) {
        return;
    }
    
    self.playResolutionLabel.stringValue = [NSString stringWithFormat:@"Resolution: %d x %d", (int)size.width, (int)size.height];
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

#endif // _Module_Play
