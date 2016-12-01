//
//  PwAdsNativeAdDelegate.m
//  TestCocos
//
//  Created by Sergey on 7/29/16.
//
//

#include "PwAdsBannerAdHelper.h"
#include "PwAdsX.h"

@implementation PwAdsBannerAdHelper

PWAdsBannerView *_bannerView;

- (id)init
{
    self = [super init];
    if (self)
    {
    }
    return self;
}

- (void) showBannerAd: (bool) isTestMode
      is3dBannerShown: (bool) is3dBanner
               zoneId: (const char*) zoneId
           creativeId:(const char*) creativeId;{
    
    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"7268";
    
    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];
    
    CCLOG("3dBanner = %i" , is3dBanner);
    if(_bannerView != nil)
    {
        [_bannerView removeFromSuperview];
        _bannerView = nil;
        
        if( _spinner != NULL)
        {
            [_spinner removeFromSuperview];
            _spinner = NULL;
        }
    }
    
    if(_bannerView == nil)
    {
        UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
        
        //uiview.size.height;
        //_bannerView = [[PWAdsBannerView alloc] initWithFrame:CGRectMake(0, 518, 320, 50)];
        _bannerView = [[PWAdsBannerView alloc] initWithFrame:CGRectMake(0, 240, 320, 50)];
        _bannerView.delegate = self;
        
        if(is3dBanner)
        {
            _bannerView.loadAnimated = isTestMode;
            _bannerView.bannerAnimationTransition = PWAdsBannerAnimationTransition3DRotation;
        }
    
        [uiview addSubview: _bannerView];
    
        PWAdsRequest *adsRequest = [PWAdsRequest requestWithZoneID:kZoneID];
        adsRequest.testMode = isTestMode;
        if (creativeIdFieldText.length > 1) {
            // Set private property
            [adsRequest setValue:creativeIdFieldText forKey:@"creativeID"];
        }
        [_bannerView loadAdsRequest:adsRequest];
    }    
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    _spinner = [[UIActivityIndicatorView alloc]initWithFrame:CGRectMake(135,220,50,50)];
    _spinner.layer.cornerRadius = 05;
    CGAffineTransform transform = CGAffineTransformMakeScale(1.5f, 1.5f);
    _spinner.transform = transform;
    [_spinner startAnimating];
    [uiview addSubview:_spinner];
}

- (void) hideBannerAd
{    
    if( _bannerView != nil)
    {
        [_bannerView removeFromSuperview];
        _bannerView = nil;
    }
}

#pragma mark - PWAdsBannerViewDelegate methods

// Called when a new banner advertisement is loaded.
- (void)bannerViewDidLoadAd:(PWAdsBannerView *)bannerView {
    NSLog(@"bannerViewDidLoadAd");
    
    if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidLoadAd();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

//  Called when a banner view fails to load a new advertisement.
- (void)bannerView:(PWAdsBannerView *)bannerView didFailWithError:(NSError *)error {
    NSLog(@"bannerView:didFailWithError:");
    
    if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidFailError();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

// Called before a banner view dismisses a modal.
- (void)bannerViewWillDissmissModal:(PWAdsBannerView *)bannerView {
    NSLog(@"bannerViewWillDissmissModal:");
    
}

// Called after a banner view dismissed a modal view.
- (void)bannerViewDidDismissModal:(PWAdsBannerView *)bannerView {
    NSLog(@"bannerViewDidDismissModal:");
}

// Called before an advertisment modal is presented. This happens when use taps on an advertisment.
- (BOOL)shouldPresentModalForBannerView:(PWAdsBannerView *)bannerView {
    NSLog(@"shouldPresentModalForBannerView:");
    
    if( PwAdsX::sharedPwAdsX()->getBannerDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getBannerDelegate()->pwBannerAdDidPresentModal();
    return YES;
}

// Called before an advertisment modal is presented. This happens when use taps on an advertisment.
- (void)bannerViewWillPresentModal:(PWAdsBannerView *)bannerView;
{
    NSLog(@"bannerViewWillPresentModal");
}

// Called after an advertisment modal is presented. This happens when use taps on an advertisment.
- (void)bannerViewDidPresentModal:(PWAdsBannerView *)bannerView;
{
    NSLog(@"bannerViewDidPresentModal:");
}

// Called before user leaves the application. This happens when user taps on an advertisment.
- (BOOL)shouldLeaveApplicationForBannerView:(PWAdsBannerView *)bannerView {
    NSLog(@"shouldLeaveApplicationForBannerView:");
    return YES;
}

#pragma -
@end
