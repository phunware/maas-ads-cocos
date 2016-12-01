//
//  PwBannerAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/2/16.
//
//

#ifndef PwBannerAdsDelegate_h
#define PwBannerAdsDelegate_h
class PwBannerAdsDelegate {
public:
    virtual ~PwBannerAdsDelegate() {}
    
    virtual void pwBannerAdDidFailError(){}
    virtual void pwBannerAdDidLoadAd(){}
    virtual void pwBannerAdDidPresentModal(){}
};
#endif /* PwBannerAdsDelegate_h */
