//
//  ZGVideoTalkViewObject.h
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/18.
//  Copyright © 2020 Zego. All rights reserved.
//

#ifdef _Module_VideoTalk

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZGVideoTalkViewObject : NSObject

@property (assign) BOOL isLocal;
@property (copy) NSString *streamID;
@property (strong) NSView *view;

@end

NS_ASSUME_NONNULL_END

#endif // _Module_VideoTalk
