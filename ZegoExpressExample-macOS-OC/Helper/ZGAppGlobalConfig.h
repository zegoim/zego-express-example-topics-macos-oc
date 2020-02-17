//
//  ZGAppGlobalConfig.h
//  ZegoExpressExample
//
//  Created by jeffreypeng on 2019/8/6.
//  Copyright © 2019 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 App Environment

 - ZGAppEnvironmentTest: 测试
 - ZGAppEnvironmentOfficial: 正式
 */
typedef NS_ENUM(NSUInteger, ZGAppEnvironment) {
    ZGAppEnvironmentTest = 0,
    ZGAppEnvironmentOfficial = 1
};

/**
 Global Config Model
 *
 */
@interface ZGAppGlobalConfig : NSObject

// App ID
@property (nonatomic, assign) unsigned int appID;

// App Sign
@property (nonatomic, copy) NSString *appSign;

// Environment
@property (nonatomic, assign) ZGAppEnvironment environment;

/**
 从字典转化为当前类型实例。
 
 @param dic 字典
 @return 当前类型实例
 */
+ (instancetype)fromDictionary:(NSDictionary *)dic;

/**
 转换成 dictionary。

 @return dictionary
 */
- (NSDictionary *)toDictionary;

@end

NS_ASSUME_NONNULL_END
