//
//  ZGQuickStartViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/2.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_QuickStart

#import "ZGQuickStartViewController.h"
#import "ZGKeyCenter.h"
#import "ZGUserIDHelper.h"
#import <ZegoExpressEngine/ZegoExpressEngine.h>

@interface ZGQuickStartViewController () <ZegoEventHandler>

// Log View
@property (unsafe_unretained) IBOutlet NSTextView *logView;

// Preview and Play View
@property (weak) IBOutlet NSView *localPreviewView;
@property (weak) IBOutlet NSView *remotePlayView;

// CreateEngine
@property (assign) BOOL isTestEnv;
@property (weak) IBOutlet NSTextField *appIDLabel;
@property (weak) IBOutlet NSTextField *appSignLabel;
@property (weak) IBOutlet NSTextField *isTestEnvLabel;
@property (weak) IBOutlet NSButton *createEngineButton;

// LoginRoom
@property (copy) NSString *roomID;
@property (copy) NSString *userID;
@property (weak) IBOutlet NSTextField *roomIDLabel;
@property (weak) IBOutlet NSTextField *userIDLabel;
@property (weak) IBOutlet NSButton *loginRoomButton;

// PublishStream
@property (weak) IBOutlet NSTextField *publishStreamIDTextField;
@property (weak) IBOutlet NSButton *startPublishingButton;

// PlayStream
@property (weak) IBOutlet NSTextField *playStreamIDTextField;
@property (weak) IBOutlet NSButton *startPlayingButton;

@end

@implementation ZGQuickStartViewController

#pragma mark - Setup

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.isTestEnv = YES;
    self.roomID = @"QuickStartRoom-1";
    self.userID = [ZGUserIDHelper userID];
    
    [self setupUI];
}

- (void)setupUI {
    self.title = @"Quick Start";
    
    self.appIDLabel.stringValue = [NSString stringWithFormat:@"AppID: %u", [ZGKeyCenter appID]];
    self.appSignLabel.stringValue = [NSString stringWithFormat:@"AppSign: %@", [ZGKeyCenter appSign]];
    
    self.roomIDLabel.stringValue = [NSString stringWithFormat:@"RoomID: %@", self.roomID];
    self.userIDLabel.stringValue = [NSString stringWithFormat:@"UserID: %@", self.userID];
    self.isTestEnvLabel.stringValue = [NSString stringWithFormat:@"isTestEnv: %@", self.isTestEnv ? @"YES" : @"NO"];
}

#pragma mark - Step 1: CreateEngine

- (IBAction)createEngineButtonClick:(NSButton *)sender {
    
    unsigned int appID = [ZGKeyCenter appID];
    NSString *appSign = [ZGKeyCenter appSign];
    
    // Create ZegoExpressEngine and add self as a delegate (ZegoEventHandler)
    [ZegoExpressEngine createEngineWithAppID:appID appSign:appSign isTestEnv:self.isTestEnv scenario:ZegoScenarioGeneral eventHandler:self];
    
    // Print log
    [self appendLog:@" 🚀 Create ZegoExpressEngine"];
    
    // Add a flag to the button for successful operation
    [self.createEngineButton setTitle:@"✅ CreateEngine"];
}

#pragma mark - Step 2: LoginRoom

- (IBAction)loginRoomButtonClick:(NSButton *)sender {
    // Instantiate a ZegoUser object
    ZegoUser *user = [ZegoUser userWithUserID:self.userID];
    
    // Instantiate a ZegoRoomConfig object with the default configuration
    ZegoRoomConfig *roomConfig = [ZegoRoomConfig defaultConfig];
    
    // Login room
    [[ZegoExpressEngine sharedEngine] loginRoom:self.roomID user:user config:roomConfig];
    
    // Print log
    [self appendLog:@" 🚪 Start login room"];
}

#pragma mark - Step 3: StartPublishing

- (IBAction)startPublishingButtonClick:(NSButton *)sender {
    // Instantiate a ZegoCanvas for local preview
    ZegoCanvas *previewCanvas = [ZegoCanvas canvasWithView:self.localPreviewView];
    previewCanvas.viewMode = ZegoViewModeAspectFill;
    
    // Start preview
    [[ZegoExpressEngine sharedEngine] startPreview:previewCanvas];
    
    NSString *publishStreamID = self.publishStreamIDTextField.stringValue;
    
    // If streamID is empty @"", SDK will pop up an UIAlertController if "isTestEnv" is set to YES
    [[ZegoExpressEngine sharedEngine] startPublishing:publishStreamID];
    
    // Print log
    [self appendLog:@" 📤 Start publishing stream"];
}

#pragma mark - Step 4: StartPlaying

- (IBAction)startPlayingButtonClick:(NSButton *)sender {
    // Instantiate a ZegoCanvas for local preview
    ZegoCanvas *playCanvas = [ZegoCanvas canvasWithView:self.remotePlayView];
    playCanvas.viewMode = ZegoViewModeAspectFill;
    
    NSString *playStreamID = self.playStreamIDTextField.stringValue;
    
    // If streamID is empty @"", SDK will pop up an UIAlertController if "isTestEnv" is set to YES
    [[ZegoExpressEngine sharedEngine] startPlayingStream:playStreamID canvas:playCanvas];
    
    // Print log
    [self appendLog:@" 📥 Strat playing stream"];
}

#pragma mark - Exit

- (IBAction)destroyEngineButtonClick:(NSButton *)sender {
    [self.createEngineButton setTitle:@"CreateEngine"];
    [self.loginRoomButton setTitle:@"LoginRoom"];
    [self.startPublishingButton setTitle:@"StartPublishing"];
    [self.startPlayingButton setTitle:@"StartPlaying"];
    
    // Logout room before exiting
    [[ZegoExpressEngine sharedEngine] logoutRoom:self.roomID];
    
    // Can destroy the engine when you don't need audio and video calls
    [ZegoExpressEngine destroyEngine];
    
    // Print log
    [self appendLog:@" 🏳️ Destroy ZegoExpressEngine"];
}

- (void)viewDidDisappear {
    // Logout room before exiting
    [[ZegoExpressEngine sharedEngine] logoutRoom:self.roomID];
    
    // Can destroy the engine when you don't need audio and video calls
    [ZegoExpressEngine destroyEngine];
    
    [super viewDidDisappear];
}

#pragma mark - ZegoEventHandler Delegate

/// Room status change notification
- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode room:(NSString *)roomID {
    if (state == ZegoRoomStateConnected && errorCode == 0) {
        [self appendLog:@" 🚩 🚪 Login room success"];
        
        // Add a flag to the button for successful operation
        [self.loginRoomButton setTitle:@"✅ LoginRoom"];
    }
    
    if (errorCode != 0) {
        [self appendLog:@" 🚩 ❌ 🚪 Login room fail"];
        
        [self.loginRoomButton setTitle:@"❌ LoginRoom"];
    }
}

/// Publish stream state callback
- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode stream:(NSString *)streamID {
    if (state == ZegoPublisherStatePublishing && errorCode == 0) {
        [self appendLog:@" 🚩 📤 Publishing stream success"];
        
        // Add a flag to the button for successful operation
        [self.startPublishingButton setTitle:@"✅ StartPublishing"];
    }
    
    if (errorCode != 0) {
        [self appendLog:@" 🚩 ❌ 📤 Publishing stream fail"];
        
        [self.startPublishingButton setTitle:@"❌ StartPublishing"];
    }
}

/// Play stream state callback
- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode stream:(NSString *)streamID {
    if (state == ZegoPlayerStatePlaying && errorCode == 0) {
        [self appendLog:@" 🚩 📥 Playing stream success"];
        
        // Add a flag to the button for successful operation
        [self.startPlayingButton setTitle:@"✅ StartPlaying"];
    }
    
    if (errorCode != 0) {
        [self appendLog:@" 🚩 ❌ 📥 Playing stream fail"];
        
        [self.startPlayingButton setTitle:@"❌ StartPlaying"];
    }
}

#pragma mark - Helper Methods

/// Append Log to Top View
- (void)appendLog:(NSString *)tipText {
    if (!tipText || tipText.length == 0) {
        return;
    }
    
    NSString *oldText = self.logView.string;
    NSString *newLine = oldText.length == 0 ? @"" : @"\n";
    NSString *newText = [NSString stringWithFormat:@"%@%@%@", oldText, newLine, tipText];
    
    self.logView.string = newText;
    [self.logView scrollToEndOfDocument:nil];
}

@end

#endif // _Module_QuickStart
