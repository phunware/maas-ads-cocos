//
//  PwAdsDelegateBridge.mm
//  TestCocos
//
//  Created by Sergey on 7/25/16.
//
//

#include "PwAdsDelegateBridge.h"
#include "PwAdsX.h"

@implementation PwAdsDelegateBridge

PwAdsNativeAdHelper* nativeDelegate;
PwAdsLandingPageAdHelper* landingPageDelegate;
PwAdsBannerAdHelper * bannerDelegate;
PwAdsInterstitiailAdHelper* interstitialDelegate;
PwAdsVideoInterstitialHelper* videoInterstitial;
PwAdsRewardedVideoHelper* rewardedVideoDelegate;


+ (PwAdsDelegateBridge*) sharedInstance {
    static PwAdsDelegateBridge *pwadsDelegateBridge = nil;
    @synchronized(self) {
        if (pwadsDelegateBridge == nil)
            pwadsDelegateBridge = [[self alloc] init];
    }
    return pwadsDelegateBridge;
}

- (void)showNativeAd: (bool) isTestMode nativaAdType: (const char*) nativeAdType
              zoneId: (const char*) zoneId
          creativeId: (const char*) creativeId{
    nativeDelegate = [PwAdsNativeAdHelper new];
    [nativeDelegate showNativeAd:isTestMode nativaAdType: nativeAdType
                          zoneId: zoneId
                      creativeId: creativeId];
}

- (void)showLandingPageAd: (bool) isTestMode
                   zoneId: (const char*) zoneId
               creativeId: (const char*) creativeId{
    landingPageDelegate = [[PwAdsLandingPageAdHelper alloc ] init];
    [landingPageDelegate showLandingPage: isTestMode
                                  zoneId: zoneId
                              creativeId: creativeId];
}

- (void)showBannerAd: (bool) isTestMode
     is3dBannerShown: (bool) is3dBanner
              zoneId: (const char*) zoneId
          creativeId: (const char*) creativeId{
    bannerDelegate = [[PwAdsBannerAdHelper alloc] init];
    [bannerDelegate showBannerAd:isTestMode  is3dBannerShown: is3dBanner zoneId:zoneId creativeId:creativeId];
}

- (void)showInterstitialAd: (bool) isTestMode
                    zoneId: (const char*) zoneId
                creativeId: (const char*) creativeId {
    interstitialDelegate = [[PwAdsInterstitiailAdHelper alloc] init];
    [interstitialDelegate showInterstitial: isTestMode
                                    zoneId: zoneId
                                creativeId: creativeId];
}

- (void)showVideoInterstitialAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId{
    videoInterstitial = [[PwAdsVideoInterstitialHelper alloc] init];
    [videoInterstitial showVideoInterstitialAd: isTestMode
                                        zoneId: zoneId
                                    creativeId: creativeId];
}

- (void)loadRewardedVideoAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId
                         userId: (const char*) userId {
    rewardedVideoDelegate = [[PwAdsRewardedVideoHelper alloc] init];
    [rewardedVideoDelegate loadRewardedVideoAd: isTestMode
                                        zoneId: zoneId
                                    creativeId: creativeId
                                        userId: userId];
}

- (void)showRewardedVideoAd: (bool) isTestMode
                     zoneId: (const char*) zoneId
                 creativeId: (const char*) creativeId
           customDataString: (const char*) customDataString {
    [rewardedVideoDelegate showRewardedVideoAd: isTestMode
                                        zoneId: zoneId
                                    creativeId: creativeId
                              customDataString: customDataString];
}


- (void)hideBannerAd{
    [bannerDelegate hideBannerAd];
}

- (void)hideNativeAd{
    [nativeDelegate hideNativeAd];
}

@end
