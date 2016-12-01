//
//  PwAdsLandingPageAdHelper.h
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <PWAdvertising/PWAds.h>
#include <PWAdvertising/PWAdsLandingPage.h>

@interface PwAdsLandingPageAdHelper : NSObject<PWAdsLandingPageDelegate>

- (void)showLandingPage: (bool) isTestMode
                 zoneId: (const char*) zoneId
             creativeId: (const char*) creativeId;

@property (nonatomic, retain) PWAdsLandingPage *landingPage;
@property (retain, nonatomic) UIActivityIndicatorView *spinner;

@end
