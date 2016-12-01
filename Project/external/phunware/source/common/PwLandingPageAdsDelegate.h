//
//  PwLandingPageAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/2/16.
//
//

#ifndef PwLandingPageAdDelegate_h
#define PwLandingPageAdDelegate_h

class PwLandingPageAdsDelegate {
public:
    virtual ~PwLandingPageAdsDelegate() {}
    
    virtual void pwLandingPageAdDidFailError(){}
    virtual void pwLandingPageAdDidLoadAd(){}
    virtual void pwLandingPageAdDidDismissModal(){}
};
#endif /* PwLandingPageAdDelegate_h */
