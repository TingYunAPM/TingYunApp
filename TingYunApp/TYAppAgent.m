//
//  TYAppAgent.m
//  TYApp
//
//  Created by Kang on 17/4/27.
//  Copyright © 2017年 kang. All rights reserved.
//

#import "TYAppAgent.h"

@implementation TYAppAgent

+(void)startWithAppID:(NSString*)appId;{
    [NBSAppAgent startWithAppID:appId];
}

+(void)startWithAppID:(NSString *)appId channelId:(NSString *)channelId{
    [NBSAppAgent startWithAppID:appId channelId:channelId];
}

+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double) rate{
    [NBSAppAgent startWithAppID:appId rateOfLaunch:rate];
}

+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed{
    [NBSAppAgent startWithAppID:appId location:locationAllowed];
}

+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed rateOfLaunch:(double) rate channelId:(NSString *)channelId{
    [NBSAppAgent startWithAppID:appId location:locationAllowed rateOfLaunch:rate channelId:channelId];
}

+(void)setIgnoreBlock:(BOOL (^)(NSURLRequest* request)) block{
    [NBSAppAgent setIgnoreBlock:block];
}

+(void)setCustomerData:(NSString*)data forKey:(NSString*)key{
    [NBSAppAgent setCustomerData:data forKey:key];
}

+(void)setSetOption:(int)option{
    [NBSAppAgent setSetOption:option];
}

+(void)leaveBreadcrumb:(NSString *)breadcrumb{
    [NBSAppAgent leaveBreadcrumb:breadcrumb];
}

+(void)setUserIdentifier:(NSString *)userId{
    [NBSAppAgent setUserIdentifier:userId];
}

+ (void)trackEvent:(NSString *)eventID{
    [NBSAppAgent trackEvent:eventID];
}


+ (BOOL)tingyunAppIsStart{
    return [NBSAppAgent tingyunAppIsStart];
}



@end

@implementation TYAppAgent (Enterprise)

+(void)setRedirectURL:(NSString*)URL{
    [NBSAppAgent setRedirectURL:URL];
}

+(void)setHttpEnabled:(BOOL)isEnable{
    [NBSAppAgent setHttpEnabled:isEnable];
}

+(void)httpsAllowAnyCert{
    [NBSAppAgent httpsAllowAnyCert];
}
@end
