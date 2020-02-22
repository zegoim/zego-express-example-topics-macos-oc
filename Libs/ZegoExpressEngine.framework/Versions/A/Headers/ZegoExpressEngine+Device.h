//
//  ZegoExpressEngine+Device.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Device)

/// On/off microphone
/// @discussion This interface is used to control whether the collected audio data is used. When the microphone is turned off, the data is collected and discarded, and the microphone is still occupied.
/// @param mute Whether to turn on the microphone, YES means to turn off the microphone; NO means to turn on the microphone
- (void)muteMicrophone:(BOOL)mute;

/// Turn on/off audio output to the device
/// @discussion This interface is used to control whether the SDK needs to throw audio data to the device.
/// @param mute Whether to enable audio output to the device, YES  means to turn off the audio output; NO means turn on the audio output
- (void)muteAudioOutput:(BOOL)mute;

#if TARGET_OS_OSX
/// Choose to use an audio device
/// @discussion Only for macOS
/// @param deviceID ID of a device obtained by getAudioDeviceList
/// @param deviceType Audio device type
- (void)useAudioDevice:(NSString *)deviceID type:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_OSX
/// Get a list of audio devices
/// @discussion Only for macOS
/// @param deviceType Audio device type
/// @return Audo device List
- (NSArray<ZegoDeviceInfo *> *)getAudioDeviceList:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_IPHONE
/// On/off audio capture device
/// @discussion This interface is used to control whether to release the audio collection device. When the audio collection device is turned off, the SDK will no longer occupy the audio device. Of course, if the stream is being pushed at this time, there is no audio data.
/// @param enable Whether to enable the audio capture device, YES means to enable the audio capture device, NO means turn off the audio capture device
- (void)enableAudioCaptureDevice:(BOOL)enable;
#endif

/// On/off camera
/// @discussion This interface is used to control whether to start the camera acquisition. After the camera is turned off, video capture will not be performed. At this time, the push stream will also have no video data.
/// @param enable Whether to turn on the camera, NO means to turn off the camera; YES means to turn on the camera
- (void)enableCamera:(BOOL)enable;

#if TARGET_OS_IPHONE
/// Switch front and rear camera
/// @discussion This interface is used to control the front or rear camera
/// @param enable Whether to use the front camera. NO means using a rear camera; YES means using a front camera
- (void)useFrontCamera:(BOOL)enable;
#endif

#if TARGET_OS_OSX
/// Choose to use a video device
/// @discussion Only for macOS
/// @param deviceID ID of a device obtained by getVideoDeviceList
- (void)useVideoDevice:(NSString *)deviceID;
#endif

#if TARGET_OS_OSX
/// Get a list of video devices
/// @discussion Only for macOS
/// @return Video device List
- (NSArray<ZegoDeviceInfo *> *)getVideoDeviceList;
#endif

/// Start the sound level monitor
- (void)startSoundLevelMonitor;

/// Stop the sound level monitor
- (void)stopSoundLevelMonitor;

/// Start the audio spectrum monitor
- (void)startAudioSpectrumMonitor;

/// Stop the audio spectrum monitor
- (void)stopAudioSpectrumMonitor;

@end

NS_ASSUME_NONNULL_END
