//
//  NBSAppAgent.h
//
//  Created by yang kai on 14-3-12.
//  Copyright (c) 2014年 NBS. All rights reserved.
//

#import <Foundation/Foundation.h>

#define NBSOption_Net           1<<0
#define NBSOption_UI            1<<1
#define NBSOption_Crash         1<<2
#define NBSOption_hybrid        1<<3
#define NBSOption_Socket        1<<4
#define NBSOption_StrideApp     1<<5
#define NBSOption_ANR           1<<6
#define NBSOption_Behaviour     1<<7
#define NBSOption_CDNHeader     1<<8

void nbsCustomerAPI_logStart(NSString *eventName,id self,SEL _cmd);
void nbsCustomerAPI_logFinish(NSString *eventName,SEL _cmd);
/*
 自定义API：
 @str_eventName:可为nil，如果设置为nil，则默认为当前方法名
 warning：
 1、自定义API接口只能在同一线程中进行动态埋点，不可跨线程操作
 2、自定义API接口只能在同一方法内进行动态埋点，不可跨方法操作
 3、自定义API接口不能在异步加载中使用
 4、自定义API接口不能在递归调用中使用
 请务必遵守以上几点，否则可能导致数据不准确！
 For example：
 - (void)doSomething
 {
 beginTracer(@"doSomething")
 
 //write you code here
 
 endTracer(@"doSomething")
 }
 */

#define beginTracer(str_eventName) {\
    nbsCustomerAPI_logStart(str_eventName,self,_cmd);\
}
#define endTracer(str_eventName) {\
   nbsCustomerAPI_logFinish(str_eventName,_cmd);\
}



@interface NBSAppAgent : NSObject
/*
 启动NBSAppAgent。一般，只需本函数足矣！
 */
+(void)startWithAppID:(NSString*)appId;
/*
 @channelID:渠道ID,默认为AppStore
 */
+(void)startWithAppID:(NSString *)appId channelId:(NSString *)channelId;
/*
 rate指定了启动的概率，应该是0～1之间的一个数，0.5表示一半概率。默认100%
 */
+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double) rate;
/*
 locationAllowed指明是否使用位置服务，默认是不使用，如果app本身使用了位置服务，此函数无效。
 SDK使用位置服务的逻辑是这样的，如果app本身使用了位置服务，则SDK也使用位置信息，否则，调用本函数指明要使用位置信息，则使用位置信息。
 换句话说：如果app没有使用位置信息，而且没有调用本函数，则SDK不取位置信息（当然也不会开启位置服务）。
 */
+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed;
/*
 同时指定启动概率、是否使用位置服务、渠道ID
 */
+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed rateOfLaunch:(double) rate channelId:(NSString *)channelId;

/*
 忽略某些网络请求。block返回true的，都被忽略。
 */
+(void)setIgnoreBlock:(BOOL (^)(NSURLRequest* request)) block;
/*
 setCustomerData:forKey:的目的是这样的：通过这个方法设置的信息，会在crash时作为环境信息提交，帮助用户分析问题。此函数可以在任何地方多次调用
 */
+(void)setCustomerData:(NSString*)data forKey:(NSString*)key;
/*
 设置启动选项，SDK有几个功能，借此可以关闭某个。此函数应该在其他函数之前调用。option的值应该是NBSOption_Net、NBSOption_UI、NBSOption_Crash、NBSOption_hybrid、NBSOption_Socket的组合
 */
+(void)setSetOption:(int)option;
/*
 面包屑功能：是指用户在程序中通过该接口添加的一些信息,当程序发生崩溃时，将会把这些添加的信息，按顺序收集起来，和崩溃信息都发送给服务器
 @breadcrumb:自定义信息
*/
+(void)leaveBreadcrumb:(NSString *)breadcrumb;
/*
 设置用户标识符,不能超过64个字符
 @userId:能唯一标识一个用户的信息
 warning:为保证数据的准确性，该接口最好只设置一次
 */
+(void)setUserIdentifier:(NSString *)userId;

/*
 自定义事件：最多包含32个字符，支持中文、英文、数字、下划线，但不能包含空格或其他的转义字符
 */
+ (void)trackEvent:(NSString *)eventID;

/*
 返回一个BOOL值，代表tingyunApp是否启动
 */
+ (BOOL)tingyunAppIsStart;

/*
 关闭更新提示log。
 SDKVersion为最新的SDK版本
 */
+ (void)closeLogForUpdateHint:(NSString *)SDKVersion;
@end

/*
 Example 1:最简单的
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 
 Example 2:指定采样率 50%
 [NBSAppAgent startWithAppID:@"xxxxxxx" rateOfLaunch:0.5f];
 
 Example 3:要求采集位置信息
 [NBSAppAgent startWithAppID:@"xxxxxxx" location:YES];
 
 Example 4:忽略包含127.0.0.1的url
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 [NBSAppAgent setIgnoreBlock:^BOOL(NSURLRequest* request)
 {
 return [request.URL.absoluteString rangeOfString:@"127.0.0.1"].location!=NSNotFound;//忽略包含127.0.0.1的url
 }
 ];
 
 Example 5:使用选项启动SDK：
 [NBSAppAgent setSetOption:NBSOption_Net|NBSOption_Crash];//只开启网络和崩溃的监控，不开启UI的监控
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 
 */



#pragma mark Only for Enterprise-Edition:
@interface NBSAppAgent (Enterprise)
+(void)setRedirectURL:(NSString*)URL;//设置转向url
+(void)setHttpEnabled:(BOOL)isEnable;// 链接dc允许http而非https
+(void)httpsAllowAnyCert;//https方式链接dc时，允许任何证书，即便是自授的、伪造的
@end



