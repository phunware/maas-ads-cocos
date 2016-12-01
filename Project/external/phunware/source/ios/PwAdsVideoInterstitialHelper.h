//
//  PwAdsVideoInterstitialHelper.h
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAds.h>

@interface PwAdsVideoInterstitialHelper : NSObject<PWAdsVideoInterstitialDelegate>

- (void)showVideoInterstitialAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId;

@property (retain, nonatomic) PWAdsVideoInterstitial *videoInterstitial;
@property (retain, nonatomic) UIActivityIndicatorView *spinner;

@end
