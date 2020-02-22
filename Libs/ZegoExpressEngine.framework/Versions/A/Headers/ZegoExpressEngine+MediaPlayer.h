//
//  ZegoExpressEngine+MediaPlayer.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (MediaPlayer)

/// Create a media player instance object
/// @discussion Currently, a maximum of 4 instances can be created, after which it will return nil.
/// @return Media player instance, nil will be returned when the maximum number is exceeded
- (nullable ZegoMediaPlayer *)createMediaPlayer;

/// Destroys the media player instance object
/// @param player Player instance that needs to be released
- (void)destroyMediaPlayer:(ZegoMediaPlayer *)player;

@end

NS_ASSUME_NONNULL_END
