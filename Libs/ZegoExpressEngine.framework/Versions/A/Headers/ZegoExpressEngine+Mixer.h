//
//  ZegoExpressEngine+Mixer.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Mixer)

/// 开始混流任务
/// @param task 混流任务对象
/// @param callback 开始混流任务结果通知
- (void)startMixerTask:(ZegoMixerTask *)task callback:(nullable ZegoMixerStartCallback)callback;

/// 停止混流任务
/// @param taskID 混流任务 ID
- (void)stopMixerTask:(NSString *)taskID;

@end

NS_ASSUME_NONNULL_END
