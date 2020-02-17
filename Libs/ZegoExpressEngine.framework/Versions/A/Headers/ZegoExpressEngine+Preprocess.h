//
//  ZegoExpressEngine+Preprocess.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Preprocess)

/// 开/关回声消除
/// @discussion 打开回声消除， SDK 会对采集到的音频数据进行过滤以降低音频中的回音成分。需要在开始推流之前设置，推流开始后设置无效。
/// @param enable 是否开启回声消除，NO 表示关闭回声消除，YES 表示开启回声消除
- (void)enableAEC:(BOOL)enable;

/// 设置回声消除模式
/// @discussion 切换不同的回声消除模式以控制消除回声数据的程度。需要在开始推流之前设置。
/// @param mode 回声消除模式
- (void)setAECMode:(ZegoAECMode)mode;

/// 开/关自动增益
/// @discussion 开启自动增益后声音会被放大，但会一定程度上影响音质。需要在开始推流之前设置。
/// @param enable 是否开启自动增益，NO 表示关闭自动增益，YES 表示开启自动增益
- (void)enableAGC:(BOOL)enable;

/// 开/关噪声抑制
/// @discussion 开启噪声抑制可以使人声更加清晰。需要在开始推流之前设置，推流开始后设置无效。
/// @param enable 是否开启噪声抑制，NO 表示关闭噪声抑制，YES 表示开启噪声抑制
- (void)enableANS:(BOOL)enable;

/// 开/关美颜
/// @discussion 识别视频中的人像进行美颜。开始推流前后都可以设置。
/// @param featureBitmask 比特掩码格式，可选择同时开启 ZegoBeautifyFeature 中的几个特性
- (void)enableBeautify:(ZegoBeautifyFeature)featureBitmask;

/// 设置美颜参数
/// @param option 美颜选项参数
- (void)setBeautifyOption:(ZegoBeautifyOption *)option;

@end

NS_ASSUME_NONNULL_END
