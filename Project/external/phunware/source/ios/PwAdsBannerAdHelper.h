//
//  PwAdsNativeAdDelegate.h
//  TestCocos
//
//  Created by Sergey on 7/29/16.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAds.h>

@interface PwAdsBannerAdHelper : NSObject<PWAdsBannerViewDelegate>

- (void) showBannerAd: (bool)isTestMode
      is3dBannerShown: (bool)is3dBanner
               zoneId: (const char*) zoneId
           creativeId:(const char*) creativeId;
- (void) hideBannerAd;

@property (retain, nonatomic) UIActivityIndicatorView *spinner;

@end
