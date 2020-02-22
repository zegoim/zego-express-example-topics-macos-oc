//
//  ZegoExpressEngine+Mixer.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Mixer)

/// Start mix stream task
/// @param task Mix stream task object
/// @param callback Start mix stream task result callback notification
- (void)startMixerTask:(ZegoMixerTask *)task callback:(nullable ZegoMixerStartCallback)callback;

/// Stop mix stream task
/// @param taskID Mix stream task ID
- (void)stopMixerTask:(NSString *)taskID;

@end

NS_ASSUME_NONNULL_END
