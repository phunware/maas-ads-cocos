//
//  PwAdsInterstitiailAdHelper.m
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include "PwAdsInterstitiailAdHelper.h"
#include "PwAdsX.h"

@implementation PwAdsInterstitiailAdHelper

//static NSString * const kZoneID =  @"7983";

- (void)showInterstitial: (bool) isTestMode
                  zoneId: (const char*) zoneId
              creativeId: (const char*) creativeId{
    
    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"7983";
    
    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];
    
    _interstitial = [[PWAdsInterstitial alloc] init];
    _interstitial.delegate = self;
    
    PWAdsRequest *request = [PWAdsRequest requestWithAdZone:kZoneID];
    request.testMode = isTestMode;
    if (creativeIdFieldText.length > 1) {
        [request setValue:creativeIdFieldText forKey:@"creativeID"];
    }
    [_interstitial loadAdsRequest:request];
    
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

#pragma mark -  PWAdsInterstitialDelegate

//  Called when a new advertisement is loaded.
- (void)interstitialDidLoadAd:(PWAdsInterstitial *)interstitialAd {
    NSLog(@"interstitialDidLoadAd:");
    
    [_interstitial presentFromViewController: (UIViewController*) [UIApplication sharedApplication].keyWindow.rootViewController];
    
    if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidLoadAd();
}

//  Called when an interstitial fails to load advertisement.
- (void)interstitial:(PWAdsInterstitial *)interstitial didFailWithError:(NSError *)error {
    NSLog(@"interstitial:didFailWithError:");
    
    if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidFailError();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called before interstitial ad is dissmissed.
- (void)interstitialWillDismissModal:(PWAdsInterstitial *)interstitialAd {
    NSLog(@"interstitialWillDismissModal:");
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

- (void)interstitialDidPresentModal:(PWAdsInterstitial *)interstitialAd;
{
    NSLog(@"interstitialDidPresentModal:");
    
    if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidPresentModal();
}

// Called after Interstitial ad has been dismissed.
- (void)interstitialDidDismissModal:(PWAdsInterstitial *)interstitialAd {
    NSLog(@"interstitialDidDismissModal:");
    
    if( PwAdsX::sharedPwAdsX()->getInterstitialDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getInterstitialDelegate()->pwInterstitialAdDidDismissModal();
}



// Called before user leaves the application. This happens when user taps on an advertisment.
- (BOOL)shouldLeaveApplicationForInterstitial:(PWAdsInterstitial *)interstitial {
    NSLog(@"shouldLeaveApplicationForInterstitial:");
    
    return true;
}

#pragma -

@end
