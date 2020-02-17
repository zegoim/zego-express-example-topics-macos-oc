//
//  ZGUserIDHelper.h
//  ZegoExpressExample-macOS-OC
//
//  Created by Patrick Fu on 2020/2/1.
//  Copyright © 2020 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZGUserIDHelper : NSObject

/// Will return a global userID. If it does not exist, it is randomly generated and then saved in userDefaults.
@property (class, copy ,nonatomic, readonly) NSString *userID;

@property (class, copy ,nonatomic, readonly) NSString *userName;

+ (NSString *)getDeviceUUID;

+ (NSString *)getDeviceModel;

@end

NS_ASSUME_NONNULL_END
