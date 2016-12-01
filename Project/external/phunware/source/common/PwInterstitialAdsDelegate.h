//
//  PwInterstitialAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/2/16.
//
//

#ifndef PwInterstitialAdsDelegate_h
#define PwInterstitialAdsDelegate_h
class PwInterstitialAdsDelegate {
public:
    virtual ~PwInterstitialAdsDelegate() {}
    
    virtual void pwInterstitialAdDidFailError(){}
    virtual void pwInterstitialAdDidLoadAd(){}
    virtual void pwInterstitialAdDidDismissModal(){}
    virtual void pwInterstitialAdDidPresentModal(){}
};
#endif /* PwInterstitialAdsDelegate_h */
