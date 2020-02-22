//
//  ZGUserDefaults.m
//  ZegoExpressExample-macOS-OC
//
//  Created by jeffreypeng on 2019/7/23.
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZGUserDefaults.h"

@implementation ZGUserDefaults

+ (NSUserDefaults *)standardUserDefaults {
    @throw ([NSException exceptionWithName:@"Not support this method. Please init `ZGUserDefaults` with `init` method" reason:nil userInfo:nil]);
    return nil;
}

- (instancetype)initWithSuiteName:(NSString *)suitename {
    @throw ([NSException exceptionWithName:@"Not support this method. Please init `ZGUserDefaults` with `init` method" reason:nil userInfo:nil]);
    return nil;
}

- (instancetype)init {
    self = [super initWithSuiteName:@"group.im.zego.ZegoExpressExample-macOS-OC"];
    return self;
}

@end
