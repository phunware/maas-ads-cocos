//
//  PwAdsX.cpp
//  TestCocos
//
//  Created by Sergey on 7/28/16.
//
//

#include "PwAdsX.h"
#include "PwAdsDelegateBridge.h"

static PwAdsX* s_pPwAdsX = NULL;

PwAdsX::PwAdsX()
{}

PwAdsX* PwAdsX::sharedPwAdsX()
{
    if (s_pPwAdsX == NULL)
    {
        s_pPwAdsX = new PwAdsX();
    }
    return s_pPwAdsX;
}

void PwAdsX::showIntersitialAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
    [[PwAdsDelegateBridge sharedInstance] showInterstitialAd: isTestMode zoneId:zoneId creativeId:creativeId];
    return;
}

void PwAdsX::showVideoIntersitialAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
    [[PwAdsDelegateBridge sharedInstance] showVideoInterstitialAd: isTestMode zoneId:zoneId creativeId:creativeId];
    return;
}

void PwAdsX::showNativeAd(const char* nativeAd, bool isTestMode, const char* zoneId, const char* creativeId)
{
    [[PwAdsDelegateBridge sharedInstance] showNativeAd: isTestMode nativaAdType: nativeAd zoneId:zoneId creativeId:creativeId];
    return;
}

void PwAdsX::showLandingPageAd(bool isTestMode, const char* zoneId, const char* creativeId)
{
    [[PwAdsDelegateBridge sharedInstance] showLandingPageAd: isTestMode zoneId:zoneId creativeId:creativeId];
    return;
}

void PwAdsX::showBannerAd(bool isTestMode, bool is3dBanner, const char* zoneId, const char* creativeId)
{
    [[PwAdsDelegateBridge sharedInstance] showBannerAd:isTestMode is3dBannerShown:is3dBanner zoneId:zoneId creativeId:creativeId];
    return;
}

void PwAdsX::loadRewardedVideoAd(bool isTestMode, const char* zoneId, const char* creativeId, const char* userId)
{
    [[PwAdsDelegateBridge sharedInstance] loadRewardedVideoAd:isTestMode zoneId:zoneId creativeId:creativeId userId:userId];
    return;
}

void PwAdsX::showRewardedVideoAd(bool isTestMode, const char* zoneId, const char* creativeId, const char* customDataString)
{
    [[PwAdsDelegateBridge sharedInstance] showRewardedVideoAd:isTestMode zoneId:zoneId creativeId:creativeId customDataString:customDataString];
    return;
}

void PwAdsX::hideBannerAd()
{
    [[PwAdsDelegateBridge sharedInstance] hideBannerAd];
    return;
}

void PwAdsX::hideNativeAd()
{
    [[PwAdsDelegateBridge sharedInstance] hideNativeAd];
    return;
}