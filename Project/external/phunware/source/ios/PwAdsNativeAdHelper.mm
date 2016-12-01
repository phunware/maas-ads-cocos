//
//  PwAdsNativeAdHelper.m
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/5/16.
//
//

#include "PwAdsNativeAdHelper.h"
#include "PwAdsX.h"

#include "NativeIconAdUnitView.h"
#include "Native3UpAdUnitView.h"
#include "NativeCleanAdUnitView.h"

@implementation PwAdsNativeAdHelper{
    NativeAdHorizontalAligment _3UpAdUnitlayoutAligment;
}

//static NSString * const kZoneID = @"64477";

static NSString * const kNativeContentStream =  @"Content Stream";
static NSString * const kNativeNewsFeed =  @"News Feed";
static NSString * const kNativeAppWall =  @"App Wall";
static NSString * const kNativeContentWall =  @"Content Wall";
static NSString * const kNativeClean = @"Clean";
static NSString * const kNative3Up = @"3Up";
static NSString * const kNative3UpWith2Ads = @"3UpWith2Ads";
static NSString * const kNative3UpWith1Ad = @"3UpWith1Ad";
static NSString * const kNativeIcon = @"Single Icon";
static NSString * const kNativeIcons = @"Multi Icon";

UIView *currentView;

- (void)showNativeAd: (bool)isTestMode nativaAdType: (const char *) nativeAdType
              zoneId: (const char*) zoneId
          creativeId: (const char*) creativeId{
    
    NSString * creativeIdFieldText = @"";
    NSString * kZoneID =  @"64477";
    
    if(strlen(zoneId)>0)
        kZoneID = [[NSString alloc] initWithCString:zoneId encoding:NSUTF8StringEncoding];
    if(strlen(creativeId)>0)
        creativeIdFieldText = [[NSString alloc] initWithCString:creativeId encoding:NSUTF8StringEncoding];
    
    if(currentView != nil)
    {
        [currentView removeFromSuperview];
        currentView = nil;
    }
    
    if(currentView == nil)
    {
        _adsType = nativeAdType;
    
        _pwNativeLoader = [[PWAdsNativeAdLoader alloc] init];
        _pwNativeLoader.delegate = self;
    
        // Create ad request with the specified Zone ID.
        PWAdsRequest *adsRequest = [PWAdsRequest requestWithZoneID:kZoneID];
    
        adsRequest.testMode = isTestMode;
        if (creativeIdFieldText.length > 1) {
            // Set private property
            [adsRequest setValue:creativeIdFieldText forKey:@"creativeID"];
        }
        // You can set the number of ad object you want to request, default is 1.
        adsRequest.numberOfAds = 1;
    
        [_pwNativeLoader loadAdsRequest:adsRequest];
        NSLog(@"nativeView != nil");
    }
    
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    //add spiner
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    _spinner = [[UIActivityIndicatorView alloc]initWithFrame:CGRectMake(screenWidth / 2 - 25 ,screenHeight / 2 - 25 ,50 ,50)];
    _spinner.layer.cornerRadius = 05;
    CGAffineTransform transform = CGAffineTransformMakeScale(1.5f, 1.5f);
    _spinner.transform = transform;
    [_spinner startAnimating];
    [uiview addSubview:_spinner];
}

- (void)hideNativeAd
{
    if(currentView != nil)
    {
        [currentView removeFromSuperview];
        currentView = nil;
    }
}

#pragma mark Create All types of Ads
- (void)showNativeAdContentStream:(PWAdsNativeAd *)newAd{
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    BOOL changeBackgroundColor = FALSE;
    BOOL showBorder = TRUE;
    BOOL showIcon = TRUE;
    
    CGFloat width = 300, height = 200;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    
    PWAdsNativeAdView * nativeView = [[PWAdsNativeAdView alloc] initWithFrame:CGRectMake(x,y,width,height)];
    nativeView.delegate = self;
    nativeView.nativeAd = newAd;
    nativeView.tag = 82;
    
    if(changeBackgroundColor) {
        nativeView.backgroundColor = [UIColor lightGrayColor];
    }
    
    if(showBorder) {
        nativeView.layer.borderColor = [UIColor lightGrayColor].CGColor;
        nativeView.layer.borderWidth = 1.0;
        nativeView.layer.cornerRadius = 10.0;
    }
    
    [uiview addSubview:nativeView];
    
    
    int startingPointX = 5;
    
    UILabel *sponsoredLabel = [[UILabel alloc] init];
    [sponsoredLabel setFrame:CGRectMake(startingPointX,0,270,20)];
    sponsoredLabel.textColor=[UIColor grayColor];
    sponsoredLabel.userInteractionEnabled=YES;
    sponsoredLabel.font = [UIFont italicSystemFontOfSize:11];
    
    NSString *usableString = self.sponsoredStrings[arc4random_uniform((int)[self.sponsoredStrings count])];
    sponsoredLabel.text = [usableString uppercaseString];
    
    sponsoredLabel.textAlignment = NSTextAlignmentRight;
    [nativeView addSubview:sponsoredLabel];
    
    UILabel *titleLabel = [[UILabel alloc] init];
    [titleLabel setFrame:CGRectMake(startingPointX,10,280,20)];
    titleLabel.backgroundColor=[UIColor clearColor];
    titleLabel.textColor=[UIColor blackColor];
    titleLabel.userInteractionEnabled=YES;
    titleLabel.font = [UIFont systemFontOfSize:12];
    titleLabel.text = newAd.adTitle;
    [nativeView addSubview:titleLabel];
    
    if(newAd.adText) {
        UILabel *textLabel = [[UILabel alloc] init];
        [textLabel setFrame:CGRectMake(startingPointX,30,280,100)];
        textLabel.backgroundColor=[UIColor clearColor];
        textLabel.textColor=[UIColor blackColor];
        textLabel.userInteractionEnabled=YES;
        textLabel.font = [UIFont systemFontOfSize:8];
        textLabel.numberOfLines = 2;
        textLabel.text = newAd.adText;
        [textLabel sizeToFit];
        [nativeView addSubview:textLabel];
    }
    
    if(newAd.adIconURL && showIcon) {
        UIImageView *iconView = [[UIImageView alloc] initWithFrame:CGRectMake(startingPointX, 40, 30, 30)];
        iconView.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:newAd.adIconURL]]];
        [nativeView addSubview:iconView];
        startingPointX += 40;
    }
    
    for(int i=0; i < [newAd.adRating intValue]; i++) {
        CGRect ratingFrame = CGRectMake(startingPointX, 45, 20, 20);
        UIImageView *ratingView = [[UIImageView alloc] initWithFrame:ratingFrame];
        ratingView.image = [UIImage imageNamed:@"star"];
        startingPointX = startingPointX + 20;
        [nativeView addSubview:ratingView];
    }
    if ([newAd.adRating floatValue] > [newAd.adRating intValue]) {
        CGRect ratingFrame = CGRectMake(startingPointX, 45, 20, 20);
        UIImageView *ratingView = [[UIImageView alloc] initWithFrame:ratingFrame];
        ratingView.image = [UIImage imageNamed:@"halfstar"];
        startingPointX = startingPointX + 20;
        [nativeView addSubview:ratingView];
    }
    
    if(newAd.adCTA) {
        UILabel *CTALabel = [[UILabel alloc] init];
        [CTALabel setFrame:CGRectMake(220,45,70,25)];
        CTALabel.backgroundColor=[UIColor clearColor];
        CTALabel.textColor = [UIColor colorWithRed:0.110f green:0.647f blue:0.122f alpha:1.00f];
        CTALabel.userInteractionEnabled=YES;
        CTALabel.font = [UIFont boldSystemFontOfSize:12];
        CTALabel.numberOfLines = 1;
        CTALabel.text = [newAd.adCTA uppercaseString];
        CTALabel.layer.borderColor = [UIColor colorWithRed:0.110f green:0.647f blue:0.122f alpha:1.00f].CGColor;
        CTALabel.layer.borderWidth = 1.0;
        CTALabel.layer.cornerRadius = 2.5;
        CTALabel.adjustsFontSizeToFitWidth = TRUE;
        CTALabel.minimumScaleFactor = .75;
        CTALabel.textAlignment = NSTextAlignmentCenter;
        [nativeView addSubview:CTALabel];
    }
    
    UIWebView *webview=[[UIWebView alloc]initWithFrame:CGRectMake(40, 70, 220,123)];
    NSString *htmlString;
    
    if(newAd.adHTML) {
        if(changeBackgroundColor) {
            htmlString = [NSString stringWithFormat:@"<html><style>html{background-color:#AAA;}img{width:100%%; padding:0; margin:0;}</style>%@</html>", newAd.adHTML];
        } else {
            htmlString = [NSString stringWithFormat:@"<html><style>html{/*background-color:#AAA;*/}img{width:100%%; padding:0; margin:0;}</style>%@</html>", newAd.adHTML];
        }
        
        [webview loadHTMLString:htmlString baseURL:nil];
        webview.userInteractionEnabled = FALSE;
        webview.backgroundColor = [UIColor lightGrayColor];
        [nativeView addSubview:webview];
    }
    
    currentView = nativeView;
}

-(void)showIconsAdUnit:(NSArray *)newAds{
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    for (UIView *view in uiview.subviews) {
        [view removeFromSuperview];
    }
    
    CGFloat width = 300, height = newAds.count * 90 + 10;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    NativeIconAdUnitView *iconAdView = [[NativeIconAdUnitView alloc] initWithFrame:CGRectMake(x, y, width, height)];
    iconAdView.delegate = self;
    [iconAdView showIconAdUnit:newAds];
    [uiview addSubview:iconAdView];
    
    currentView = iconAdView;
     
}

-(void)showNativeClean:(PWAdsNativeAd *)newAd {
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    for (UIView *view in uiview.subviews) {
        [view removeFromSuperview];
    }
    CGFloat width = 300, height = 70;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    NativeCleanAdUnitView *cleanAdView = [[NativeCleanAdUnitView alloc] initWithFrame:CGRectMake(x, y, width, height)];
    cleanAdView.delegate = self;
    [cleanAdView showCleanAdUnit:newAd];
    [uiview addSubview:cleanAdView];
    
    currentView = cleanAdView;
}

-(void)show3UpAdUnit:(NSArray *)newAds {
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    for (UIView *view in uiview.subviews) {
        [view removeFromSuperview];
    }
    CGFloat width = 300, height = 210;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    Native3UpAdUnitView * Native3upAdView = [[Native3UpAdUnitView alloc] initWithFrame:CGRectMake(x, y, width, height)];
    Native3upAdView.delegate =self;
    [Native3upAdView show3UpAdUnit:newAds layoutType:_3UpAdUnitlayoutAligment];
    _3UpAdUnitlayoutAligment = (NativeAdHorizontalAligment)((_3UpAdUnitlayoutAligment +1) % 3);
    [uiview addSubview:Native3upAdView];
    
    currentView =Native3upAdView;
}

- (void)showNativeAdNewsFeed:(PWAdsNativeAd *)newAd withYOffset:(int)offset {
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    for (UIView *view in uiview.subviews) {
        [view removeFromSuperview];
    }
    
    BOOL showBorder = TRUE;
    BOOL showIcon = TRUE;
    
    CGFloat width = 300, height = 70;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    
    PWAdsNativeAdView *adView = [[PWAdsNativeAdView alloc] initWithFrame:CGRectMake(x,y,width,height)];
    adView.delegate = self;
    adView.nativeAd = newAd;
    
    if(showBorder) {
        adView.layer.borderColor = [UIColor lightGrayColor].CGColor;
        adView.layer.borderWidth = 1.0;
    }
    
    adView.tag = offset+111;
    
    [uiview addSubview:adView];
    
    
    int startingPointX = 5;
    
    
    UILabel *sponsoredLabel = [[UILabel alloc] init];
    [sponsoredLabel setFrame:CGRectMake(startingPointX,0,290,20)];
    sponsoredLabel.textColor=[UIColor grayColor];
    sponsoredLabel.userInteractionEnabled=YES;
    sponsoredLabel.font = [UIFont italicSystemFontOfSize:11];
    
    NSString *usableString = self.sponsoredStrings[arc4random_uniform((int)[self.sponsoredStrings count])];
    sponsoredLabel.text = [usableString uppercaseString];
    
    sponsoredLabel.textAlignment = NSTextAlignmentRight;
    [adView addSubview:sponsoredLabel];
    
    if(newAd.adIconURL && showIcon) {
        UIImageView *iconView = [[UIImageView alloc] initWithFrame:CGRectMake(startingPointX, 10, 50, 50)];
        iconView.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:newAd.adIconURL]]];
        [adView addSubview:iconView];
        startingPointX = startingPointX + 60;
    }
    
    UILabel *titleLabel = [[UILabel alloc] init];
    [titleLabel setFrame:CGRectMake(startingPointX,12,300,20)];
    titleLabel.backgroundColor=[UIColor clearColor];
    titleLabel.textColor=[UIColor blackColor];
    titleLabel.userInteractionEnabled=YES;
    titleLabel.font = [UIFont boldSystemFontOfSize:12];
    titleLabel.text = newAd.adTitle;
    [adView addSubview:titleLabel];
    
    for(int i=0; i < [newAd.adRating intValue]; i++) {
        CGRect ratingFrame = CGRectMake(startingPointX, 30, 20, 20);
        UIImageView *ratingView = [[UIImageView alloc] initWithFrame:ratingFrame];
        ratingView.image = [UIImage imageNamed:@"star"];
        startingPointX = startingPointX + 20;
        [adView addSubview:ratingView];
    }
    if ([newAd.adRating floatValue] > [newAd.adRating intValue]) {
        CGRect ratingFrame = CGRectMake(startingPointX, 30, 20, 20);
        UIImageView *ratingView = [[UIImageView alloc] initWithFrame:ratingFrame];
        ratingView.image = [UIImage imageNamed:@"halfstar"];
        startingPointX = startingPointX + 20;
        [adView addSubview:ratingView];
    }
    
    if(newAd.adCTA) {
        UILabel *CTALabel = [[UILabel alloc] init];
        [CTALabel setFrame:CGRectMake(220,30,70,25)];
        CTALabel.backgroundColor=[UIColor clearColor];
        CTALabel.textColor = [UIColor colorWithRed:0.110f green:0.647f blue:0.122f alpha:1.00f];
        CTALabel.userInteractionEnabled=YES;
        CTALabel.font = [UIFont boldSystemFontOfSize:12];
        CTALabel.numberOfLines = 1;
        CTALabel.text = [newAd.adCTA uppercaseString];
        CTALabel.layer.borderColor = [UIColor colorWithRed:0.110f green:0.647f blue:0.122f alpha:1.00f].CGColor;
        CTALabel.layer.borderWidth = 1.0;
        CTALabel.layer.cornerRadius = 2.5;
        CTALabel.adjustsFontSizeToFitWidth = TRUE;
        CTALabel.minimumScaleFactor = .75;
        CTALabel.textAlignment = NSTextAlignmentCenter;
        [adView addSubview:CTALabel];
        //[CTALabel addGestureRecognizer:tapGestureRecognizer];
    }
    
    currentView = adView;
}


- (void)showNativeAdContentWall:(PWAdsNativeAd *)newAd {
    
    UIView* uiview = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    
    for (UIView *view in uiview.subviews) {
        [view removeFromSuperview];
    }
    
    BOOL changeBackgroundColor = FALSE;
    BOOL showBorder = TRUE;
    
    
    CGFloat width = 300, height = 200;
    CGFloat x = CGRectGetMidX(uiview.bounds) - width/2;
    CGFloat y = CGRectGetMidY(uiview.bounds) - height/2;
    
    PWAdsNativeAdView *adView = [[PWAdsNativeAdView alloc] initWithFrame:CGRectMake(x,y,width,height)];
    adView.delegate = self;
    adView.nativeAd = newAd;
    adView.tag = 82;
    
    if(changeBackgroundColor) {
        adView.backgroundColor = [UIColor lightGrayColor];
    }
    
    if(showBorder) {
        adView.layer.borderColor = [UIColor lightGrayColor].CGColor;
        adView.layer.borderWidth = 1.0;
        adView.layer.cornerRadius = 10.0;
    }
    
    [uiview addSubview:adView];
    
    int startingPointX = 5;
    
    if(newAd.adHTML) {
        UIWebView *webview=[[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 300,175)];
        
        NSString *htmlString;
        if(changeBackgroundColor) {
            htmlString = [NSString stringWithFormat:@"<html><style>html{background-color:#AAA;}body{margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;}img{width:100%%; padding:0; margin:0; border-bottom-left-radius: 10px; border-bottom-right-radius: 10px;}</style>%@</html>", newAd.adHTML];
        } else {
            htmlString = [NSString stringWithFormat:@"<html><style>html{/*background-color:#AAA;*/} body{margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;} img{width:100%%; padding:0; margin:0; border-bottom-left-radius: 10px; border-bottom-right-radius: 10px;}</style>%@</html>", newAd.adHTML];
        }
        
        [webview loadHTMLString:htmlString baseURL:nil];
        webview.userInteractionEnabled = FALSE;
        webview.backgroundColor = [UIColor lightGrayColor];
        webview.layer.cornerRadius = 10.0;
        [webview setClipsToBounds:TRUE];
        [adView addSubview:webview];
    }
    
    UILabel *sponsoredLabel = [[UILabel alloc] init];
    [sponsoredLabel setFrame:CGRectMake(startingPointX,180,290,20)];
    sponsoredLabel.textColor=[UIColor grayColor];
    sponsoredLabel.userInteractionEnabled=YES;
    sponsoredLabel.font = [UIFont italicSystemFontOfSize:11];
    
    NSString *usableString = self.sponsoredStrings[arc4random_uniform((int)[self.sponsoredStrings count])];
    sponsoredLabel.text = [usableString uppercaseString];
    
    sponsoredLabel.textAlignment = NSTextAlignmentRight;
    [adView addSubview:sponsoredLabel];
    
    currentView = adView;
}

- (void)showNativeAdAppWall:(NSArray *)nativeAds{
    
    int offset = 0;
    for (PWAdsNativeAd *ad in nativeAds) {
        [self showNativeAdNewsFeed:ad withYOffset:offset];
        offset = offset + 75;
    }
}

#pragma mark -

- (NSArray *)sponsoredStrings {
    return @[@"advertisement", @"sponsored", @"brought to you by", @"our sponsors", @"sponsored content", @"you may also like"];
}

#pragma mark - PWAdsNativeAdLoaderDelegate

//  Called when a new native advertisement is loaded.
- (void)nativeAdLoaderDidLoadAds:(NSArray *)nativeAds {
    NSLog(@"nativeAdLoaderDidLoadAds:");
    NSString* _selectedNativeAd = [[NSString alloc] initWithCString:_adsType encoding:NSUTF8StringEncoding];
    
    if ([_selectedNativeAd isEqualToString:kNativeContentStream]) {
        [self showNativeAdContentStream:[nativeAds lastObject]];
    }
    else if ([_selectedNativeAd isEqualToString:kNativeNewsFeed]) {
        [self showNativeAdNewsFeed:[nativeAds lastObject] withYOffset:0];
    }
    else if ([_selectedNativeAd isEqualToString:kNativeAppWall]) {
        [self showNativeAdAppWall:nativeAds];
    }
    else if ([_selectedNativeAd isEqualToString:kNativeContentWall]) {
        [self showNativeAdContentWall:[nativeAds lastObject]];
    }
    else if ([_selectedNativeAd isEqualToString:kNativeClean]) {
        [self showNativeClean:[nativeAds lastObject]];
    }
    else if ([_selectedNativeAd isEqualToString:kNative3Up]) {
        NSMutableArray *showAds = [NSMutableArray arrayWithArray:nativeAds];
        while (showAds.count < 3) {
            [showAds addObjectsFromArray:showAds];
        }
        [self show3UpAdUnit:showAds];
    }
    else if ([_selectedNativeAd isEqualToString:kNative3UpWith2Ads]) {
        NSMutableArray *showAds = [NSMutableArray arrayWithArray:nativeAds];
        if (showAds.count <2) {
            [showAds addObjectsFromArray:showAds];
        }
        [self show3UpAdUnit:showAds];
    }
    else if ([_selectedNativeAd isEqualToString:kNative3UpWith1Ad]){
        [self show3UpAdUnit:nativeAds];
    }
    else if ([_selectedNativeAd isEqualToString:kNativeIcon] || [_selectedNativeAd isEqualToString:kNativeIcons]) {
        NSMutableArray *showAds = [NSMutableArray arrayWithArray:nativeAds];
        if ([_selectedNativeAd isEqualToString:kNativeIcons]) {
            if (showAds.count > 0) {
                while (showAds.count < 3) {
                    [showAds addObjectsFromArray:nativeAds];
                }
            }
        }
        [self showIconsAdUnit:showAds];
    }
    
    if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidLoadAd();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

//  Called when a native advertisement fails to load.
- (void)nativeAdLoader:(PWAdsNativeAdLoader *)loader didFailWithError:(NSError *)error {
    NSLog(@"nativeAdLoader:didFailWithError:");
    
    if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidFailError();
    
    if( _spinner != NULL)
    {
        [_spinner removeFromSuperview];
        _spinner = NULL;
    }
}

#pragma mark -

#pragma mark - PWAdsNativeAdViewDelegate

// Called before a native advertisment modal is presented.
- (void)nativeAdViewWillPresentModal:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"nativeAdViewWillPresentModal:");
}

//  Called after a native advertisment modal is presented.
- (void)nativeAdViewDidPresentModal:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"nativeAdViewDidPresentModal:");
    
    if( PwAdsX::sharedPwAdsX()->getNativeDelegate() != NULL)
        PwAdsX::sharedPwAdsX()->getNativeDelegate()->pwNativeAdDidPresentModal();
}

//  Called before a native ad dismisses a modal.
- (void)nativeAdViewWillDissmissModal:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"nativeAdViewWillDissmissModal:");
}

//  Called after a native ad dismissed a modal view.
- (void)nativeAdViewDidDismissModal:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"nativeAdViewDidDismissModal:");
}

//  Called before an advertisment modal is presented. This happens when use taps on an advertisment.
- (BOOL)shouldPresentModalForNativeAdView:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"shouldPresentModalForNativeAdView:");
    return YES;
}

//  Called before user leaves the application. This happens when user taps on an advertisment.
- (BOOL)shouldLeaveApplicationForNativeAdView:(PWAdsNativeAdView *)nativeAdView {
    NSLog(@"shouldLeaveApplicationForNativeAdView:");
    return YES;
}

#pragma mark -

@end
