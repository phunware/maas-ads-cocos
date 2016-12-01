//
//  PwVideoInterstitialAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#ifndef PwVideoInterstitialAdsDelegate_h
#define PwVideoInterstitialAdsDelegate_h

//#include "cocos2d.h"

class PwVideoInterstitialAdsDelegate {
public:
    virtual ~PwVideoInterstitialAdsDelegate() {}
    
    virtual void pwVideoInterstitialAdDidFailError(){}
    virtual void pwVideoInterstitialAdDidLoadAd(){}
    virtual void pwVideoInterstitialAdDidPresentModal(){}
};
#endif /* PwVideoInterstitialAdsDelegate_h */
