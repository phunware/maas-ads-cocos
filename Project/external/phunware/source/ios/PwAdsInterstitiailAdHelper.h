//
//  PwAdsInterstitiailAdHelper.h
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAds.h>

@interface PwAdsInterstitiailAdHelper : NSObject<PWAdsInterstitialDelegate>

- (void)showInterstitial: (bool) isTestMode
                  zoneId: (const char*) zoneId
              creativeId: (const char*) creativeId;

@property (retain, nonatomic) PWAdsInterstitial *interstitial;
@property (retain, nonatomic) UIActivityIndicatorView *spinner;

@end
