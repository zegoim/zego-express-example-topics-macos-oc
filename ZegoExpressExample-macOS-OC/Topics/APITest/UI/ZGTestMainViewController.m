//
//  ZGTestMainViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2019/10/25.
//  Copyright © 2019 Zego. All rights reserved.
//

#ifdef _Module_Test

#import "ZGTestMainViewController.h"
#import "ZGTestTopicManager.h"
#import "ZGAppGlobalConfigManager.h"

NSString* const ZGTestTopicKey_RoomID = @"kRoomID";
NSString* const ZGTestTopicKey_UserID = @"kUserID";
NSString* const ZGTestTopicKey_PublishStreamID = @"kPublishStreamID";
NSString* const ZGTestTopicKey_PlayStreamID = @"kPlayStreamID";
NSString* const ZGTestTopicKey_AudioBitrate = @"kAudioBitrate";
NSString* const ZGTestTopicKey_CaptureVolume = @"kCaptureVolume";
NSString* const ZGTestTopicKey_PlayVolume = @"kPlayVolume";
NSString* const ZGTestTopicKey_BeautifyFeature = @"kBeautifyFeature";

@interface ZGTestMainViewController () <ZGTestDataSource>

@property (strong) ZGTestTopicManager *manager;

@property (weak) IBOutlet NSView *publishView;
@property (weak) IBOutlet NSView *playView;
@property (unsafe_unretained) IBOutlet NSTextView *logTextView;


@property (weak) IBOutlet NSTextField *publishQualityLabel;
@property (weak) IBOutlet NSTextField *publishResolutionLabel;
@property (weak) IBOutlet NSTextField *playQualityLabel;
@property (weak) IBOutlet NSTextField *playResolutionLabel;

@property (weak) IBOutlet NSTextField *appIDTextField;
@property (weak) IBOutlet NSTextField *appSignTextField;
@property (weak) IBOutlet NSButton *isTestEnvCheckbox;
@property (weak) IBOutlet NSPopUpButton *scenarioPopUp;
@property (weak) IBOutlet NSButton *createEngineButton;
@property (weak) IBOutlet NSButton *destroyEngineButton;

@property (weak) IBOutlet NSTextField *roomIDTextField;
@property (weak) IBOutlet NSTextField *userIDTextField;
@property (weak) IBOutlet NSButton *loginRoomButton;
@property (weak) IBOutlet NSButton *logoutRoomButton;

@property (weak) IBOutlet NSTextField *publishStreamIDTextField;
@property (weak) IBOutlet NSButton *startPreviewButton;
@property (weak) IBOutlet NSButton *stopPreviewButton;
@property (weak) IBOutlet NSButton *startPublishButton;
@property (weak) IBOutlet NSButton *stopPublishButton;

@property (weak) IBOutlet NSTextField *playStreamIDTextField;
@property (weak) IBOutlet NSButton *startPlay;
@property (weak) IBOutlet NSButton *stopPlay;

@end

@implementation ZGTestMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidAppear {
    self.manager = [[ZGTestTopicManager alloc] init];
    [self.manager setZGTestDataSource:self];
    [self setupUI];
}

- (void)viewWillDisappear {
    [self.manager destroyEngine];
}

- (void)setupUI {
    [self.publishView setWantsLayer:YES];
    [self.publishView.layer setBackgroundColor:[[NSColor lightGrayColor] CGColor]];
    [self.playView setWantsLayer:YES];
    [self.playView.layer setBackgroundColor:[[NSColor lightGrayColor] CGColor]];
    
    self.publishQualityLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.3];
    self.publishQualityLabel.textColor = [NSColor whiteColor];
    
    self.publishResolutionLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.3];
    self.publishResolutionLabel.textColor = [NSColor whiteColor];
    
    self.playQualityLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.3];
    self.playQualityLabel.textColor = [NSColor whiteColor];
    
    self.playResolutionLabel.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.3];
    self.playResolutionLabel.textColor = [NSColor whiteColor];
    
    self.logTextView.string = @"";
    self.logTextView.backgroundColor = [NSColor colorWithWhite:0.0 alpha:0.2];
    self.logTextView.textColor = [NSColor whiteColor];
    
    ZGAppGlobalConfig *appConfig = [[ZGAppGlobalConfigManager sharedManager] globalConfig];
    
    self.appIDTextField.stringValue = [NSString stringWithFormat:@"%d", appConfig.appID];
    self.appSignTextField.stringValue = appConfig.appSign;
    
    [self.scenarioPopUp selectItemAtIndex:0];
    
    NSString *savedRoomID = [self savedValueForKey:ZGTestTopicKey_RoomID];
    NSString *savedUserID = [self savedValueForKey:ZGTestTopicKey_UserID];
    self.roomIDTextField.stringValue = savedRoomID == nil ? @"" : savedRoomID;
    self.userIDTextField.stringValue = savedUserID == nil ? @"" : savedUserID;
    
    NSString *savedPublishStreamID = [self savedValueForKey:ZGTestTopicKey_PublishStreamID];
    self.publishStreamIDTextField.stringValue = savedPublishStreamID == nil ? @"" : savedPublishStreamID;
    
    NSString *savedPlayStreamID = [self savedValueForKey:ZGTestTopicKey_PlayStreamID];
    self.playStreamIDTextField.stringValue = savedPlayStreamID == nil ? @"" : savedPlayStreamID;
}


- (IBAction)createEngineClick:(NSButton *)sender {
    [self.manager createEngineWithAppID:[self.appIDTextField.stringValue intValue] appSign:self.appSignTextField.stringValue isTestEnv:self.isTestEnvCheckbox.state == NSControlStateValueOn scenario:(ZegoScenario)self.scenarioPopUp.indexOfSelectedItem];
}

- (IBAction)destroyEngineClick:(NSButton *)sender {
    [self.manager destroyEngine];
}

- (IBAction)loginRoomClick:(NSButton *)sender {
    [self.manager loginRoom:self.roomIDTextField.stringValue userID:self.userIDTextField.stringValue userName:self.userIDTextField.stringValue];
    [self saveValue:self.roomIDTextField.stringValue forKey:ZGTestTopicKey_RoomID];
    [self saveValue:self.userIDTextField.stringValue forKey:ZGTestTopicKey_UserID];
}

- (IBAction)logoutRoomClick:(NSButton *)sender {
    [self.manager logoutRoom:self.roomIDTextField.stringValue];
}

- (IBAction)startPreviewClick:(NSButton *)sender {
    [self.manager startPreview:[ZegoCanvas canvasWithView:self.publishView]];
}

- (IBAction)stopPreviewClick:(NSButton *)sender {
    [self.manager stopPreview];
}

- (IBAction)startPublishingStreamClick:(NSButton *)sender {
    [self.manager startPublishingStream:self.publishStreamIDTextField.stringValue];
    [self saveValue:self.publishStreamIDTextField.stringValue forKey:ZGTestTopicKey_PublishStreamID];
}

- (IBAction)stopPublishingStreamClick:(NSButton *)sender {
    [self.manager stopPublishingStream];
}

- (IBAction)startPlayingClick:(NSButton *)sender {
    [self.manager startPlayingStream:self.playStreamIDTextField.stringValue canvas:[ZegoCanvas canvasWithView:self.playView]];
    [self saveValue:self.playStreamIDTextField.stringValue forKey:ZGTestTopicKey_PlayStreamID];
}

- (IBAction)stopPlayClick:(NSButton *)sender {
    [self.manager stopPlayingStream:self.playStreamIDTextField.stringValue];
}

- (void)appendLog:(NSString *)tipText {
    if (!tipText || tipText.length == 0) {
        return;
    }
    
    NSString *oldText = self.logTextView.string;
    NSString *newLine = oldText.length == 0 ? @"" : @"\n";
    NSString *newText = [NSString stringWithFormat:@"%@%@%@", oldText, newLine, tipText];
    
    self.logTextView.string = newText;
    [self.logTextView scrollToEndOfDocument:nil];
}


#pragma mark - ZGTestDataSource

- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality {
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
    [text appendFormat:@"FPS: %d fps\n", (int)quality.videoSendFPS];
    [text appendFormat:@"Bitrate: %.2f kb/s \n", quality.videoKBPS];
    [text appendFormat:@"HardwareEncode: %@ \n", quality.isHardwareEncode ? @"✅" : @"❎"];
    [text appendFormat:@"NetworkQuality: %@", networkQuality];
    self.publishQualityLabel.stringValue = text;
}

- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality {
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
    self.playQualityLabel.stringValue = text;
}

- (void)onPublisherVideoSizeChanged:(CGSize)size {
    self.publishResolutionLabel.stringValue = [NSString stringWithFormat:@"Resolution: %.fx%.f", size.width, size.height];
}

- (void)onPlayerVideoSizeChanged:(CGSize)size {
    self.playResolutionLabel.stringValue = [NSString stringWithFormat:@"Resolution: %.fx%.f", size.width, size.height];
}

- (void)onActionLog:(NSString *)logInfo {
    [self appendLog:logInfo];
}

@end

#endif // _Module_Test
