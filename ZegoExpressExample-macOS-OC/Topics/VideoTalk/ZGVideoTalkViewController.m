//
//  ZGVideoTalkViewController.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/18.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_VideoTalk

#import "ZGVideoTalkViewController.h"
#import "ZGAppGlobalConfigManager.h"
#import "ZGUserIDHelper.h"
#import "NSFlippedView.h"
#import "ZGVideoTalkViewObject.h"
#import <ZegoExpressEngine/ZegoExpressEngine.h>

// The number of displays per row of the stream view
NSInteger const ZGVideoTalkStreamViewColumnPerRow = 3;
// Stream view spacing
CGFloat const ZGVideoTalkStreamViewSpacing = 10.f;


@interface ZGVideoTalkViewController () <ZegoEventHandler>

@property (strong) ZegoExpressEngine *engine;

/// Login room ID
@property (copy) NSString *roomID;

/// User canvas object of participating video call users
@property (strong) NSMutableArray<ZGVideoTalkViewObject *> *allUserViewObjectList;

/// Local user view object
@property (nonatomic, strong) ZGVideoTalkViewObject *localUserViewObject;

/// Local user ID
@property (copy) NSString *localUserID;

/// Local stream ID
@property (copy) NSString *localStreamID;

/// Labels
@property (weak) IBOutlet NSTextField *roomIDLabel;
@property (weak) IBOutlet NSTextField *roomStateLabel;

/// Container
@property (weak) IBOutlet NSFlippedView *containerView;

/// Whether to enable the camera
@property (assign) BOOL enableCamera;
@property (weak) IBOutlet NSButton *cameraCheckBox;

/// Whether to mute the microphone
@property (weak) IBOutlet NSButton *microphoneCheckBox;
@property (assign) BOOL muteMicrophone;

/// Whether to enable speaker
@property (assign) BOOL muteSpeaker;
@property (weak) IBOutlet NSButton *speakerCheckBox;

@end

@implementation ZGVideoTalkViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.roomID = @"VideoTalkRoom-1";
    
    // Use user ID as stream ID
    self.localUserID = ZGUserIDHelper.userID;
    self.localStreamID = [NSString stringWithFormat:@"s-%@", _localUserID];
    
    self.allUserViewObjectList = [NSMutableArray<ZGVideoTalkViewObject *> array];
    
    self.enableCamera = YES;
    self.muteMicrophone = NO;
    self.muteSpeaker = YES;
    
    [self setupUI];
    
    [self createEngine];
    
    [self joinTalkRoom];
}

- (void)setupUI {
    self.title = @"Video Talk";
    
    self.cameraCheckBox.state = _enableCamera ? NSControlStateValueOn : NSControlStateValueOff;
    self.microphoneCheckBox.state = !_muteMicrophone ? NSControlStateValueOn : NSControlStateValueOff;
    self.speakerCheckBox.state = _muteSpeaker ? NSControlStateValueOn : NSControlStateValueOff;
    
    self.roomIDLabel.stringValue = [NSString stringWithFormat:@"RoomID: %@", _roomID];
    
    self.roomStateLabel.stringValue = @"Not Connected 🔴";
    
    // Add local user video view object
    [self.allUserViewObjectList addObject:self.localUserViewObject];
    [self rearrangeVideoTalkViewObjects];
}

#pragma mark - Actions

- (void)createEngine {
    ZGAppGlobalConfig *appConfig = [[ZGAppGlobalConfigManager sharedManager] globalConfig];
    
    ZGLogInfo(@" 🚀 Create ZegoExpressEngine");
    self.engine = [ZegoExpressEngine createEngineWithAppID:appConfig.appID appSign:appConfig.appSign isTestEnv:appConfig.isTestEnv scenario:appConfig.scenario eventHandler:self];
}

- (void)joinTalkRoom {
    // Login room
    ZGLogInfo(@" 🚪 Login room, roomID: %@", _roomID);
    [self.engine loginRoom:_roomID user:[ZegoUser userWithUserID:_localUserID]];
    
    // Set the publish video configuration
    [self.engine setVideoConfig:[ZegoVideoConfig configWithPreset:ZegoVideoConfigPreset720P]];
    
    // Get the local user's preview view and start preview
    ZegoCanvas *previewCanvas = [ZegoCanvas canvasWithView:self.localUserViewObject.view];
    previewCanvas.viewMode = ZegoViewModeAspectFill;
    ZGLogInfo(@" 🔌 Start preview");
    [self.engine startPreview:previewCanvas];
    
    // Local user start publishing
    ZGLogInfo(@" 📤 Start publishing stream, streamID: %@", _localStreamID);
    [self.engine startPublishingStream:_localStreamID];
}

- (void)exitRoom {
    // It is recommended to logout room when stopping the video call.
    ZGLogInfo(@" 🚪 Logout room, roomID: %@", _roomID);
    [self.engine logoutRoom:_roomID];
    
    // And you can destroy the engine when there is no need to call.
    ZGLogInfo(@" 🏳️ Destroy ZegoExpressEngine");
    [ZegoExpressEngine destroyEngine:nil];
}

/// Exit room when VC disappear
- (void)viewDidDisappear {
    [self exitRoom];
    [super viewDidDisappear];
}

- (IBAction)onToggleCameraCheckBox:(NSButton *)sender {
    _enableCamera = sender.state == NSControlStateValueOn ? YES : NO;
    [self.engine enableCamera:_enableCamera];
}

- (IBAction)onToggleMicrophoneCheckBox:(NSButton *)sender {
    _muteMicrophone = sender.state == NSControlStateValueOn ? NO : YES;
    [self.engine muteMicrophone:_muteMicrophone];
}

- (IBAction)onToggleSpeakerCheckBox:(NSButton *)sender {
    _muteSpeaker = sender.state == NSControlStateValueOn ? NO : YES;
    [self.engine muteSpeaker:_muteSpeaker];
}


#pragma mark - ViewObject Methods

/// Rearrange participant flow view
- (void)rearrangeVideoTalkViewObjects {
    for (ZGVideoTalkViewObject *obj in _allUserViewObjectList) {
        if (obj.view != nil) {
            [obj.view removeFromSuperview];
        }
    }
    
    NSInteger columnPerRow = ZGVideoTalkStreamViewColumnPerRow;
    CGFloat viewSpacing = ZGVideoTalkStreamViewSpacing;
    CGFloat viewWidth = CGRectGetWidth(self.view.bounds);
    CGFloat playViewWidth = (viewWidth - (columnPerRow + 1)*viewSpacing) /columnPerRow;
    CGFloat playViewHeight = 1.5f * playViewWidth;
    
    NSInteger i = 0;
    for (ZGVideoTalkViewObject *obj in _allUserViewObjectList) {
        if (obj.view == nil) {
            continue;
        }
        
        NSInteger cloumn = i % columnPerRow;
        NSInteger row = i / columnPerRow;
        
        CGFloat x = viewSpacing + cloumn * (playViewWidth + viewSpacing);
        CGFloat y = viewSpacing + row * (playViewHeight + viewSpacing);
        obj.view.frame = CGRectMake(x, y, playViewWidth, playViewHeight);
        
        [self.containerView addSubview:obj.view];
        i++;
    }
}

- (ZGVideoTalkViewObject *)getViewObjectWithStreamID:(NSString *)streamID {
    __block ZGVideoTalkViewObject *existObj = nil;
    [self.allUserViewObjectList enumerateObjectsUsingBlock:^(ZGVideoTalkViewObject * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if ([obj.streamID isEqualToString:streamID]) {
            existObj = obj;
            *stop = YES;
        }
    }];
    return existObj;
}

/// Add a view of user who has entered the room and play the user stream
- (void)addRemoteViewObjectIfNeedWithStreamID:(NSString *)streamID {
    ZGVideoTalkViewObject *viewObject = [self getViewObjectWithStreamID:streamID];
    if (!viewObject) {
        viewObject = [ZGVideoTalkViewObject new];
        viewObject.isLocal = NO;
        viewObject.streamID = streamID;
        viewObject.view = [NSView new];
        [self.allUserViewObjectList addObject:viewObject];
    }
    
    ZegoCanvas *playCanvas = [ZegoCanvas canvasWithView:viewObject.view];
    playCanvas.viewMode = ZegoViewModeAspectFill;
    
    [self.engine startPlayingStream:streamID canvas:playCanvas];
    ZGLogInfo(@" 📥 Start playing stream, streamID: %@", streamID);
}

/// Remove view of user who has left the room and stop playing stream
- (void)removeViewObjectWithStreamID:(NSString *)streamID {
    ZGVideoTalkViewObject *obj = [self getViewObjectWithStreamID:streamID];
    if (obj) {
        [self.allUserViewObjectList removeObject:obj];
        [obj.view removeFromSuperview];
    }
    
    [self.engine stopPlayingStream:streamID];
    ZGLogInfo(@" 📥 Stop playing stream, streamID: %@", streamID);
}

#pragma mark - ZegoEventHandler

- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode extendedData:(NSDictionary *)extendedData roomID:(NSString *)roomID {
    if (errorCode != 0) {
        ZGLogError(@" 🚩 ❌ 🚪 Room state error, errorCode: %d", errorCode);
    } else {
        if (state == ZegoRoomStateConnected) {
            ZGLogInfo(@" 🚩 🚪 Login room success");
            self.roomStateLabel.stringValue = @"Connected 🟢";
        } else if (state == ZegoRoomStateConnecting) {
            ZGLogInfo(@" 🚩 🚪 Requesting login room");
            self.roomStateLabel.stringValue = @"Connecting 🟡";
        } else if (state == ZegoRoomStateDisconnected) {
            ZGLogInfo(@" 🚩 🚪 Logout room");
            self.roomStateLabel.stringValue = @"Not Connected 🔴";
        }
    }
}

/// Refresh the remote streams list
- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID {
    ZGLogInfo(@" 🚩 🌊 Room Stream Update Callback: %lu, StreamsCount: %lu, roomID: %@", (unsigned long)updateType, (unsigned long)streamList.count, roomID);
    NSArray<NSString *> *allStreamIDList = [_allUserViewObjectList valueForKeyPath:@"streamID"];
    
    if (updateType == ZegoUpdateTypeAdd) {
        for (ZegoStream *stream in streamList) {
            ZGLogInfo(@" 🚩 🌊 --- [Add] StreamID: %@, UserID: %@", stream.streamID, stream.user.userID);
            if (![allStreamIDList containsObject:stream.streamID]) {
                [self addRemoteViewObjectIfNeedWithStreamID:stream.streamID];
            }
        }
    } else if (updateType == ZegoUpdateTypeDelete) {
        for (ZegoStream *stream in streamList) {
            ZGLogInfo(@" 🚩 🌊 --- [Delete] StreamID: %@, UserID: %@", stream.streamID, stream.user.userID);
            [self removeViewObjectWithStreamID:stream.streamID];
        }
    }
    
    [self rearrangeVideoTalkViewObjects];
}

#pragma mark - Getter

- (ZGVideoTalkViewObject *)localUserViewObject {
    if (!_localUserViewObject) {
        _localUserViewObject = [ZGVideoTalkViewObject new];
        _localUserViewObject.isLocal = YES;
        _localUserViewObject.streamID = _localStreamID;
        _localUserViewObject.view = [NSView new];
    }
    return _localUserViewObject;
}

@end

#endif // _Module_VideoTalk
