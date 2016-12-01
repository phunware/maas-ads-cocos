//
//  PwAdsRewardedVideoHelper.m
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include "PwAdsRewardedVideoHelper.h"
#include "PwAdsX.h"

@implementation PwAdsRewardedVideoHelper

//static NSString * const kZoneID =  @"22219"; // @"75395"
//UIActivityIndicatorView *spinner = NULL;

- (void)loadRewardedVideoAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId
                         userId: (const char*) userId {

    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"78393";
    NSString * kUserID = @"1234567";

    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];

    kUserID = [[NSString alloc] initWithCString:userId encoding:NSUTF8StringEncoding];

    NSString * testModeValue = (isTestMode ? @"true" : @"false");
    NSLog(@"PwAdsRewardedVideoHelper::loadRewardedVideoAd: isTestMode=%@, zoneId=%@, creativeId=%@, userId=%@", testModeValue, kZoneID, creativeIdFieldText, kUserID);

    _adsRequest = [PWAdsRequest requestWithZoneID:kZoneID];
    _adsRequest.testMode = NO;
    //adsRequest.testMode = isTestMode;
    if (creativeIdFieldText.length > 1) {
        // Set private property
        [_adsRequest setValue:creativeIdFieldText forKey:@"creativeID"];
        
    }
    _adsRequest.userID = kUserID;

    [self loadAdsWithRequest:_adsRequest];
    
    //spiner
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    _spinner = [[UIActivityIndicatorView alloc]initWithFrame:CGRectMake(135,220,50,50)];
    _spinner.layer.cornerRadius = 05;
    CGAffineTransform transform = CGAffineTransformMakeScale(1.5f, 1.5f);
    _spinner.transform = transform;
    [_spinner startAnimating];
    [uiview addSubview:_spinner];
}

- (void)showRewardedVideoAd: (bool) isTestMode
                     zoneId: (const char*) zoneId
                 creativeId: (const char*) creativeId
           customDataString: (const char*) customDataString {

    NSString* _customDataString = [NSString stringWithUTF8String: customDataString];
    NSLog(@"showRewardedVideoAd: customDataString=%@", _customDataString);
    if (!_rewardedVideo)
    {
        NSLog(@"showRewardedVideoAd: _rewardedVideo is nullish... ...");
        return;
    }
    _adsRequest.customData = [self dictionaryFromJSONString:_customDataString];
    [_rewardedVideo presentFromViewController: [UIApplication sharedApplication].keyWindow.rootViewController];
}

#pragma mark - Load request;

- (void)loadAdsWithRequest:(PWAdsRequest *)adsRequest {
    NSLog(@"PwAdsRewardedVideoHelper::loadAdsWithRequest...");
    _rewardedVideo = [PWAdsRewardedVideo new];
    _rewardedVideo.delegate = self;

    [_rewardedVideo loadAdsRequest:adsRequest];
}

#pragma mark - PWAdsRewardedVideoDelegate

- (void)rewardedVideoDidLoadAd:(PWAdsRewardedVideo *)rewardedVideo withAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdsRewardedVideoDelegate - rewardedVideoDidLoadAd: adExtensionData = %@", [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);
    NSDictionary *eDict = @{@"remainingViews" : adExtensionData[@"remainingViews"],
                            @"successesCount" : adExtensionData[@"SuccessfulViewings"],
                            @"startsCount"    : adExtensionData[@"Starts"],
                            @"errorCode"      : adExtensionData[@"Error"]};
    NSMutableDictionary *mutableEDict = [NSMutableDictionary dictionaryWithDictionary:eDict];
    const char *cStringEDict = [[self jsonStringFromNSDictionary:mutableEDict] cStringUsingEncoding:NSASCIIStringEncoding];

    if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()->pwRewardedVideoAdDidLoadAd(cStringEDict);

    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}


- (void)rewardedVideoDidEndPlaybackSuccessfully:(PWAdsRewardedVideo *)rewardedVideo withRVResponseObject:(NSDictionary *)customData andAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdsRewardedVideoDelegate - rewardedVideoDidEndPlaybackSuccessfully:\n\tcustomData = %@\n\tadExtensionData = %@", [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:customData]], [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);

    NSDictionary *rDict = @{@"remainingViews" : [NSNumber numberWithInt:[customData[@"remainingViews"] intValue]],
                            @"currencyId"     : customData[@"currencyID"],
                            @"rewardAmount"   : [NSNumber numberWithInt:[customData[@"amount"] intValue]],
                            @"successesCount" : adExtensionData[@"SuccessfulViewings"],
                            @"startsCount"    : adExtensionData[@"Starts"],
                            @"errorCode"      : adExtensionData[@"Error"],
                            @"customData"     : customData[@"customData"]};
    NSMutableDictionary *mutableRDict = [NSMutableDictionary dictionaryWithDictionary:rDict];
    const char *cStringRDict = [[self jsonStringFromNSDictionary:mutableRDict] cStringUsingEncoding:NSASCIIStringEncoding];

    if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()->pwRewardedVideoAdDidSucceed(cStringRDict);

    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

- (void)rewardedVideo:(PWAdsRewardedVideo *)rewardedVideo didFailError:(NSError *)error withAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdsRewardedVideoDelegate - didFailError:\n\tNSError error.description = %@,\n\terror.code = %zd\n\tadExtensionData = %@", error.description, error.code, [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);

    NSDictionary *eDict = @{@"remainingViews" : adExtensionData[@"remainingViews"],
                            @"successesCount" : adExtensionData[@"SuccessfulViewings"],
                            @"startsCount"    : adExtensionData[@"Starts"],
                            @"errorCode"      : adExtensionData[@"Error"]};
    NSMutableDictionary *mutableEDict = [NSMutableDictionary dictionaryWithDictionary:eDict];
    const char *cStringEDict = [[self jsonStringFromNSDictionary:mutableEDict] cStringUsingEncoding:NSASCIIStringEncoding];

    if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()->pwRewardedVideoAdDidDismissModal(cStringEDict);

    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

- (void)rewardedVideoDidPresentModal:(PWAdsRewardedVideo *)rewardedVideo withAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdRewardedVideoDelegate - rewardedVideoDidPresentModal: adExtensionData = %@", [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);
}

- (void)rewardedVideoWillDismissModal:(PWAdsRewardedVideo *)rewardedVideo withAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdRewardedVideoDelegate - rewardedVideoWillDismissModal: adExtensionData = %@", [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);
}

- (void)rewardedVideoDidDismissModal:(PWAdsRewardedVideo *)rewardedVideo withAdExtensionData:(NSDictionary *)adExtensionData
{
    NSLog(@"PWAdsRewardedVideoDelegate - rewardedVideoDidDismissModal: adExtensionData = %@", [self jsonStringFromNSDictionary:[NSMutableDictionary dictionaryWithDictionary:adExtensionData]]);

    NSDictionary *eDict = @{@"remainingViews" : adExtensionData[@"remainingViews"],
                            @"successesCount" : adExtensionData[@"SuccessfulViewings"],
                            @"startsCount"    : adExtensionData[@"Starts"],
                            @"errorCode"      : adExtensionData[@"Error"]};
    NSMutableDictionary *mutableEDict = [NSMutableDictionary dictionaryWithDictionary:eDict];
    const char *cStringEDict = [[self jsonStringFromNSDictionary:mutableEDict] cStringUsingEncoding:NSASCIIStringEncoding];

    if( PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getRewardedVideoDelegate()->pwRewardedVideoAdDidDismissModal(cStringEDict);

    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

#pragma -

-(NSMutableDictionary *)dictionaryFromJSONString:(NSString *)jsonString {
    NSData *webData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:webData options:0 error:&error];
    NSMutableDictionary *mutableDict = [NSMutableDictionary dictionaryWithDictionary:jsonDict];
    return mutableDict;
}
-(NSString *)jsonStringFromNSDictionary:(NSMutableDictionary *)nsDict {
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:nsDict options:0 error:&error];
    NSString *dataString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    return dataString;
}

@end
