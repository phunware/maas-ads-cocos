//
//  PwAdsVideoInterstitialHelper.m
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#include "PwAdsVideoInterstitialHelper.h"
#include "PwAdsX.h"

@implementation PwAdsVideoInterstitialHelper

//static NSString * const kZoneID =  @"22219"; // @"75395"
//UIActivityIndicatorView *spinner = NULL;

- (void)showVideoInterstitialAd: (bool) isTestMode
                         zoneId: (const char*) zoneId
                     creativeId: (const char*) creativeId{
    
    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"22219";
    
    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];
    
    _videoInterstitial = [PWAdsVideoInterstitial new];
    _videoInterstitial.delegate = self;
    
    PWAdsRequest *adsRequest = [PWAdsRequest requestWithZoneID:kZoneID];
    adsRequest.testMode = isTestMode;
    if (creativeIdFieldText.length > 1) {
        // Set private property
        [adsRequest setValue:creativeIdFieldText forKey:@"creativeID"];
    }
    [_videoInterstitial loadAdsRequest:adsRequest];
    
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

#pragma mark - PwAdsVideoInterstitialHelper

// Called when the adsLoader receives a video and is ready to play (required).
- (void)videoInterstitialDidLoadAd:(PWAdsVideoInterstitial *)videoInterstitial {
    NSLog(@"videoInterstitialDidLoadAd:");
    
    // Video ad is loaded. Now present the video interstitial.
    [_videoInterstitial presentFromViewController: [UIApplication sharedApplication].keyWindow.rootViewController];
    if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getVideoDelegate()->pwVideoInterstitialAdDidLoadAd();
}

- (void)videoInterstitialDidPresentModal:(PWAdsVideoInterstitial *)videoInterstitial{
    NSLog(@"videoInterstitial:didPresentModal:");
    
    if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getVideoDelegate()->pwVideoInterstitialAdDidPresentModal();
}

// Called when a video interstitial fails to load ad.
- (void)videoInterstitial:(PWAdsVideoInterstitial *)videoInterstitial didFailError:(NSError *)error {
    NSLog(@"videoInterstitial:didFailError:");
    
    if( PwAdsX::sharedPwAdsX()->getVideoDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getVideoDelegate()->pwVideoInterstitialAdDidFailError();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called before video interstitial dismisses video modal.
- (void)videoInterstitialWillDismissModal:(PWAdsVideoInterstitial *)videoInterstitial {
    NSLog(@"videoInterstitialWillDismissModal:");
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called after video interstitial dismisses video modal.
- (void)videoInterstitialDidDismissModal:(PWAdsVideoInterstitial *)videoInterstitial {
    NSLog(@"videoInterstitialDidDismissModal:");
}

#pragma -
@end
