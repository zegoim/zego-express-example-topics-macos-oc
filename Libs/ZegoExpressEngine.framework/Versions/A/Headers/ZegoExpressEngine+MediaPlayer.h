//
//  ZegoExpressEngine+MediaPlayer.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (MediaPlayer)

/// 创建媒体播放器实例对象
/// @discussion 目前最多支持创建 4 个实例，超过后将返回 nil
/// @return 媒体播放器实例，超过最大数量限制后将返回 nil
- (nullable ZegoMediaPlayer *)createMediaPlayer;

/// 销毁媒体播放器实例对象
/// @param player 需要释放的播放器实例
- (void)destroyMediaPlayer:(ZegoMediaPlayer *)player;

@end

NS_ASSUME_NONNULL_END
