//
//  NativeIconAdUnitView.h
//  PWAdvertising
//
//  Created by John Zhao on 5/2/16.
//  Copyright © 2016 Phunware, Inc. All rights reserved.
//

#import <PWAdvertising/PWAdsNativeAdView.h>

@interface NativeIconAdUnitView : UIView

@property (nonatomic, assign) id<PWAdsNativeAdViewDelegate> delegate;

-(void)showIconAdUnit:(NSArray *)nativeAds;

@end
