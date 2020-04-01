//
//  AppDelegate.m
//  ZegoExpressExample-macOS-OC
//
//  Created by Randy Qiu on 2018/9/27.
//  Copyright © 2018年 Zego. All rights reserved.
//

#import "AppDelegate.h"
#import "ZGTopicsTableViewController.h"
#import "ZGUserIDHelper.h"
#import "ZGTestMainViewController.h"

#import "ZegoLog.h"
#import "ZegoTTYLogger.h"
#import "ZegoDiskLogger.h"
#import "ZegoRAMStoreLogger.h"

@interface AppDelegate () <ZGTopicsTableViewControllerDelegate>

@property (weak) IBOutlet NSWindow *window;
@property (weak) IBOutlet ZGTopicsTableViewController *topicsController;
@property (weak) IBOutlet NSView *contentContainer;

@property (strong) NSArray<NSString*> *topicList;

@property (strong) NSViewController* currentController;
@property (strong) NSMutableDictionary<NSString*, NSViewController*> *comps;

@end

NSDictionary<NSString*, NSString*>* g_Topic2NibName;

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self configZegoLog];
    
    self.comps = [NSMutableDictionary dictionary];
    
    NSMutableArray *topicList = [NSMutableArray array];
    
#ifdef _Module_QuickStart
    [topicList addObject:_Module_QuickStart];
#endif
#ifdef _Module_Publish
    [topicList addObject:_Module_Publish];
#endif
#ifdef _Module_Play
    [topicList addObject:_Module_Play];
#endif
#ifdef _Module_VideoTalk
    [topicList addObject:_Module_VideoTalk];
#endif
#ifdef _Module_MediaPlayer
    [topicList addObject:_Module_MediaPlayer];
#endif
#ifdef _Module_MediaSideInfo
    [topicList addObject:_Module_MediaSideInfo];
#endif
#ifdef _Module_ScalableVideoCoding
    [topicList addObject:_Module_ScalableVideoCoding];
#endif
#ifdef _Module_MediaRecord
    [topicList addObject:_Module_MediaRecord];
#endif
#ifdef _Module_CustomVideoCapture
    [topicList addObject:_Module_CustomVideoCapture];
#endif
#ifdef _Module_ExternalVideoRender
    [topicList addObject:_Module_ExternalVideoRender];
#endif
#ifdef _Module_ExternalVideoFilter
    [topicList addObject:_Module_ExternalVideoFilter];
#endif
#ifdef _Module_Test
    [topicList addObject:_Module_Test];
#endif

    self.topicList = topicList;
    
    self.topicsController.delegate = self;
    [self.topicsController setTopicList:self.topicList];
    
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application {
    // Completely close application when click the red `close` button
    return YES;
}

- (void)configZegoLog {
    ZegoTTYLogger *ttyLogger = [ZegoTTYLogger new];
    ttyLogger.level = kZegoLogLevelDebug;
    ZegoRAMStoreLogger *ramLogger = [ZegoRAMStoreLogger new];
    ramLogger.level = kZegoLogLevelDebug;
    ZegoDiskLogger *diskLogger = [ZegoDiskLogger new];
    diskLogger.level = kZegoLogLevelDebug;
    
    [ZegoLog addLogger:ttyLogger];
    [ZegoLog addLogger:ramLogger];
    [ZegoLog addLogger:diskLogger];
}

#pragma mark - ZGTopicTableViewControllerDelegate

- (void)onTopicSelected:(NSString *)topic {
    NSLog(@"%s: %@", __func__, topic);
    
    [self.currentController.view removeFromSuperview];
    
    NSViewController* vc = nil;
    
#ifdef _Module_QuickStart
    if ([topic isEqualToString:_Module_QuickStart]) {
        vc = [[NSStoryboard storyboardWithName:@"QuickStart" bundle:nil] instantiateInitialController];
    }
#endif
    
#ifdef _Module_Publish
    if ([topic isEqualToString:_Module_Publish]) {
        vc = [[NSStoryboard storyboardWithName:@"PublishStream" bundle:nil] instantiateInitialController];
    }
#endif
    
#ifdef _Module_Play
    if ([topic isEqualToString:_Module_Play]) {
        vc = [[NSStoryboard storyboardWithName:@"PlayStream" bundle:nil] instantiateInitialController];
    }
#endif
    
#ifdef _Module_VideoTalk
    if ([topic isEqualToString:_Module_VideoTalk]) {
        vc = [[NSStoryboard storyboardWithName:@"VideoTalk" bundle:nil] instantiateInitialController];
    }
#endif
    
#ifdef _Module_Test
    if ([topic isEqualToString:_Module_Test]) {
        vc = [[NSStoryboard storyboardWithName:@"Test" bundle:nil] instantiateInitialController];
    }
#endif

#ifdef _Module_MediaPlayer
    if ([topic isEqualToString:_Module_MediaPlayer]) { // show media player page
        vc = [[ZGMediaPlayerViewController alloc] initWithNibName:@"ZGMediaPlayerViewController" bundle:nil];
    }
#endif
    
#ifdef _Module_MediaSideInfo
    if ([topic isEqualToString:_Module_MediaSideInfo]) {
        vc = [[ZGMediaSideInfoViewController alloc] initWithNibName:@"ZGMediaSideInfoViewController" bundle:nil];
    }
#endif
    
#ifdef _Module_ScalableVideoCoding
    if ([topic isEqualToString:_Module_ScalableVideoCoding]) {
        vc = [[NSStoryboard storyboardWithName:@"SVC" bundle:nil] instantiateInitialController];
    };
#endif
    
#ifdef _Module_MediaRecord
    if ([topic isEqualToString:_Module_MediaRecord]) {
        vc = [[ZegoMediaRecordViewController alloc] initWithNibName:@"ZegoMediaRecordViewController" bundle:nil];
    };
#endif
    
#ifdef _Module_CustomVideoCapture
    if ([topic isEqualToString:_Module_CustomVideoCapture]) {
        NSStoryboard *sb = [NSStoryboard storyboardWithName:@"CustomVideoCapture" bundle:nil];
        vc = [sb instantiateInitialController];
    };
#endif
    
#ifdef _Module_ExternalVideoRender
    if ([topic isEqualToString:_Module_ExternalVideoRender]) {
        NSStoryboard *sb = [NSStoryboard storyboardWithName:@"ZGExternalVideoRender" bundle:nil];
        vc = [sb instantiateInitialController];
    };
#endif
    
#ifdef _Module_ExternalVideoFilter
    if ([topic isEqualToString:_Module_ExternalVideoFilter]) {
        NSStoryboard *sb = [NSStoryboard storyboardWithName:@"ZGExternalVideoFilter" bundle:nil];
        vc = [sb instantiateInitialController];
    };
#endif

    self.currentController = vc;
    [self.comps setObject:vc forKey:topic];

    if (vc) {
        NSView* view = vc.view;
        [self.contentContainer addSubview:view];
        NSArray* v = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[view]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(view)];
        NSArray* h = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(view)];
        
        [self.contentContainer addConstraints:v];
        [self.contentContainer addConstraints:h];
    }
}

@end
