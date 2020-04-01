//
//  ZegoExpressEngine+Preprocess.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Preprocess)

/// On/off echo cancellation
///
/// Turning on echo cancellation, the SDK filters the collected audio data to reduce the echo component in the audio. It needs to be set before starting the publish, and the setting is invalid after the start of the publish.
/// @param enable Whether to enable echo cancellation, YES: enable echo cancellation, NO: disable echo cancellation
- (void)enableAEC:(BOOL)enable;

/// Set echo cancellation mode
///
/// Switch different echo cancellation modes to control the extent to which echo data is eliminated. Need to be set before starting the publish.
/// @param mode Echo cancellation mode
- (void)setAECMode:(ZegoAECMode)mode;

/// On/off automatic gain control
///
/// When the auto gain is turned on, the sound will be amplified, but it will affect the sound quality to some extent. Need to be set before starting the publish.
/// @param enable Whether to enable automatic gain control, YES: enable AGC, NO: disable AGC
- (void)enableAGC:(BOOL)enable;

/// On/off noise suppression
///
/// Turning on the noise suppression switch can reduce the noise in the audio data and make the human voice clearer. Need to be set before starting the publish.
/// @param enable Whether to enable noise suppression, YES: enable AGC, NO: disable AGC
- (void)enableANS:(BOOL)enable;

/// On/off beauty
///
/// Identify the portraits in the video for beauty. It can be set before and after the start of the publish.
/// @param featureBitmask Beauty features, bitmask format, you can choose to enable several features in [ZegoBeautifyFeature] at the same time
- (void)enableBeautify:(ZegoBeautifyFeature)featureBitmask;

/// On/off beauty
///
/// Identify the portraits in the video for beauty. It can be set before and after the start of the publish.
/// @param featureBitmask Beauty features, bitmask format, you can choose to enable several features in [ZegoBeautifyFeature] at the same time
/// @param channel Publishing stream channel.
- (void)enableBeautify:(ZegoBeautifyFeature)featureBitmask channel:(ZegoPublishChannel)channel;

/// Set beauty parameters
///
/// @param option Beauty configuration options
- (void)setBeautifyOption:(ZegoBeautifyOption *)option;

/// Set beauty parameters
///
/// @param option Beauty configuration options
/// @param channel Publishing stream channel.
- (void)setBeautifyOption:(ZegoBeautifyOption *)option channel:(ZegoPublishChannel)channel;

@end

NS_ASSUME_NONNULL_END
