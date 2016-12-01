//
//  PwAdsRwardedVideoHelper.h
//  No Ads Phunware
//
//  Created by Admin on 10/17/16.
//
//

#ifndef PwAdsRewardedVideoHelper_h
#define PwAdsRewardedVideoHelper_h

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAds.h>
#include <PWAdvertising/PWAdsRewardedVideo.h>

@interface PwAdsRewardedVideoHelper : UIViewController <PWAdsRewardedVideoDelegate>

- (void)loadRewardedVideoAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId
                         userId: (const char*) userId;
- (void)showRewardedVideoAd: (bool) isTestMode
                     zoneId: (const char*) zoneId
                 creativeId: (const char*) creativeId
           customDataString: (const char*) customDataString;

@property (retain, nonatomic) PWAdsRewardedVideo *rewardedVideo;
@property (retain, nonatomic) PWAdsRequest *adsRequest;
@property (retain, nonatomic) UIActivityIndicatorView *spinner;

@end    

#endif /* PwAdsRewardedVideoHelper_h */
