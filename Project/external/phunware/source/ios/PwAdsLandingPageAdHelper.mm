//
//  PwAdsLandingPageAdHelper.m
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include "PwAdsLandingPageAdHelper.h"
#include "PwAdsX.h"

@implementation PwAdsLandingPageAdHelper

//static NSString * const kZoneID = @"76663";

- (void) showLandingPage: (bool) isTestMode
                  zoneId: (const char*) zoneId
              creativeId: (const char*) creativeId{
    
    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"76663";
    
    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];
    
    _landingPage = [[PWAdsLandingPage alloc] init];
    _landingPage.delegate = self;
    
    PWAdsRequest *adsRequest = [PWAdsRequest requestWithZoneID:kZoneID];
    adsRequest.testMode = isTestMode;
    if (creativeIdFieldText.length > 1) {
        // Set private property
        [adsRequest setValue:creativeIdFieldText forKey:@"creativeID"];
    }
    [_landingPage loadAdsRequest:adsRequest];
    
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    _spinner = [[UIActivityIndicatorView alloc]initWithFrame:CGRectMake(screenWidth / 2 - 25 ,screenHeight / 2 - 25 ,50 ,50)];
    _spinner.layer.cornerRadius = 05;
    CGAffineTransform transform = CGAffineTransformMakeScale(1.5f, 1.5f);
    _spinner.transform = transform;
    [_spinner startAnimating];
    [uiview addSubview:_spinner];
}

#pragma mark -  PWAdsLandingPageDelegate

//  Called when a new advertisement is loaded.
- (void)landingPageDidLoadAd:(PWAdsLandingPage *)LandingPageAd {
    NSLog(@"landingPageDidLoadAd:");
    
    // LandingPage ad is loaded. Now present the LandingPage.
    [_landingPage presentFromViewController: (UIViewController*) [UIApplication sharedApplication].keyWindow.rootViewController];
    
    if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidLoadAd();
}

//  Called when an LandingPage fails to load advertisement.
- (void)landingPage:(PWAdsLandingPage *)landingPage didFailWithError:(NSError *)error {
    NSLog(@"landingPage:didFailWithError:");
    
    if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidFailError();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called before LandingPage ad is dissmissed.
- (void)landingPageWillDismissModal:(PWAdsLandingPage *)landingPageAd {
    NSLog(@"landingPageWillDismissModal:");
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called after landingPage ad has been dismissed.
- (void)landingPageDidDismissModal:(PWAdsLandingPage *)landingPageAd {
    NSLog(@"landingPageDidDismissModal:");
    
    if( PwAdsX::sharedPwAdsX()->getLandingPageDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getLandingPageDelegate()->pwLandingPageAdDidDismissModal();
}

// Called before user leaves the application. This happens when user taps on an advertisment.
-(BOOL)shouldLeaveApplicationForlandingPage:(PWAdsLandingPage *)landingPage {
    NSLog(@"shouldLeaveApplicationForLandingPage:");
    return YES;
}

#pragma -
@end
