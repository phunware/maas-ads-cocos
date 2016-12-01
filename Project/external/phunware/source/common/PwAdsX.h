//
//  PwAdsX.h
//  TestCocos
//
//  Created by Sergey on 7/28/16.
//
//

#ifndef PwAdsX_h
#define PwAdsX_h

#include <stdio.h>
#include "cocos2d.h"

#include "PwVideoInterstitialAdsDelegate.h"
#include "PwRewardedVideoAdsDelegate.h"
#include "PwInterstitialAdsDelegate.h"
#include "PwLandingPageAdsDelegate.h"
#include "PwBannerAdsDelegate.h"
#include "PwNativeAdsDelegate.h"

class  PwAdsX
{
public:
    PwAdsX();
    
    static PwAdsX* sharedPwAdsX();    
    
    virtual void showIntersitialAd(bool isTestMode = false, const char* zoneId = "", const char* creativeId = "");
    virtual void showVideoIntersitialAd(bool isTestMode = false, const char* zoneId = "", const char* creativeId = "");
    virtual void showBannerAd(bool isTestMode = false, bool is3dBanner = true, const char* zoneId = "", const char* creativeId = "");
    virtual void showNativeAd(const char* nativeAd, bool isTestMode = false, const char* zoneId = "", const char* creativeId = "");
    virtual void showLandingPageAd(bool isTestMode = false, const char* zoneId = "", const char* creativeId = "");
    virtual void loadRewardedVideoAd(bool isTestMode = false, const char* zoneId = "", const char* creativeId = "", const char* userId = "");
    virtual void showRewardedVideoAd(bool isTestMode = false, const char* zoneId = "", const char* creativeId = "", const char* customDataString = "");

    virtual void hideBannerAd();
    virtual void hideNativeAd();
    
    PwVideoInterstitialAdsDelegate* getVideoDelegate(){return videoDelegate;}
    void setVideoDelegate(PwVideoInterstitialAdsDelegate* delegate) {videoDelegate = delegate;}
    void freeVideoDelegate(){videoDelegate = NULL;}
    
    PwInterstitialAdsDelegate* getInterstitialDelegate(){return interstitialDelegate;}
    void setInterstitialDelegate(PwInterstitialAdsDelegate* delegate) {interstitialDelegate = delegate;}
    void freeInterstitialDelegate(){interstitialDelegate = NULL;}

    
    PwNativeAdsDelegate* getNativeDelegate(){return nativeDelegate;}
    void setNativeDelegate(PwNativeAdsDelegate* delegate) {nativeDelegate = delegate;}
    void freeNativeDelegate(){nativeDelegate = NULL;}

    
    PwBannerAdsDelegate* getBannerDelegate(){return bannerDelegate;}
    void setBannerDelegate(PwBannerAdsDelegate* delegate) {bannerDelegate = delegate;}
    void freeBannerDelegate(){bannerDelegate = NULL;}

    
    PwLandingPageAdsDelegate* getLandingPageDelegate(){return landingPageDelegate;}
    void setLandingPageDelegate(PwLandingPageAdsDelegate* delegate) {landingPageDelegate = delegate;}
    void freeLandingPageDelegate(){landingPageDelegate = NULL;}
    
    PwRewardedVideoAdsDelegate* getRewardedVideoDelegate(){return rewardedVideoDelegate;}
    void setRewardedVideoDelegate(PwRewardedVideoAdsDelegate* delegate) {rewardedVideoDelegate = delegate;}
    void freeRewardedVideoDelegate(){rewardedVideoDelegate = NULL;}
    
private:
    PwVideoInterstitialAdsDelegate* videoDelegate = nullptr;
    PwRewardedVideoAdsDelegate* rewardedVideoDelegate = nullptr;
    PwInterstitialAdsDelegate* interstitialDelegate = nullptr;
    PwLandingPageAdsDelegate* landingPageDelegate = nullptr;
    PwBannerAdsDelegate* bannerDelegate = nullptr;
    PwNativeAdsDelegate* nativeDelegate = nullptr;
};
#endif /* PwAdsX_h */
