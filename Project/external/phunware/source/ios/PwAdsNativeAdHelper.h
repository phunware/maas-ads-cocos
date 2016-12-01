//
//  PwAdsNativeAdHelper.h
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/5/16.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAdsNativeAd.h>
#include <PWAdvertising/PWAdsNativeAdView.h>
#include <PWAdvertising/PWAdsNativeAdLoader.h>
#include <PWAdvertising/PWAdsRequest.h>

@interface PwAdsNativeAdHelper : NSObject<PWAdsNativeAdLoaderDelegate, PWAdsNativeAdViewDelegate>

- (void)showNativeAd: (bool)isTestMode nativaAdType: (const char *)nativeAdType
              zoneId: (const char*) zoneId
          creativeId: (const char*) creativeId;
- (void)hideNativeAd;

@property (nonatomic, retain) PWAdsNativeAdLoader *pwNativeLoader;
@property (retain, nonatomic) UIActivityIndicatorView *spinner;
@property (nonatomic) const char * adsType;
@end
