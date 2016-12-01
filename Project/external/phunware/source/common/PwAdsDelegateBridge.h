//
//  PwAdsDelegateBridge.h
//  TestCocos
//
//  Created by Sergey on 7/25/16.
//
//

#include <Foundation/Foundation.h>

#include <AppController.h>
#include <PWAdvertising/PWAdsRequest.h>
#include <PwAdsBannerAdHelper.h>
#include <PwAdsNativeAdHelper.h>
#include <PwAdsLandingPageAdHelper.h>
#include <PwAdsInterstitiailAdHelper.h>
#include <PwAdsVideoInterstitialHelper.h>
#include <PwAdsRewardedVideoHelper.h>

#ifndef pwads_delegate_bridge_h
#define pwads_delegate_bridge_h

@interface PwAdsDelegateBridge : NSObject

- (void) showNativeAd: (bool)isTestMode nativaAdType: (const char*)nativaAdType zoneId:(const char*) zoneId creativeId:(const char*) creativeId;
- (void) showInterstitialAd: (bool) isTestMode zoneId:(const char*) zoneId creativeId:(const char*) creativeId;
- (void) showBannerAd:(bool)isTestMode is3dBannerShown:(bool)is3dBanner zoneId:(const char*) zoneId creativeId:(const char*) creativeId;
- (void) showVideoInterstitialAd: (bool) isTestMode zoneId:(const char*) zoneId creativeId:(const char*) creativeId;
- (void) showLandingPageAd: (bool) isTestMode zoneId:(const char*) zoneId creativeId:(const char*) creativeId;
- (void) loadRewardedVideoAd: (bool) isTestMode zoneId:(const char*) zoneId creativeId:(const char*) creativeId userId:(const char*) userId;
- (void) showRewardedVideoAd: (bool) isTestMode zoneId:(const char*) zoneId creativeId:(const char*) creativeId customDataString:(const char*) customDataString;

- (void) hideBannerAd;
- (void) hideNativeAd;

+ (PwAdsDelegateBridge*) sharedInstance;

@end
#endif
