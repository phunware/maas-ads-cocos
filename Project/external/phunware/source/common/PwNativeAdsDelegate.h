//
//  PwNativeAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/2/16.
//
//

#ifndef PwNativeAdsDelegate_h
#define PwNativeAdsDelegate_h
class PwNativeAdsDelegate {
public:
    virtual ~PwNativeAdsDelegate() {}
    
    virtual void pwNativeAdDidFailError(){}
    virtual void pwNativeAdDidLoadAd(){}
    virtual void pwNativeAdDidPresentModal(){}
};
#endif /* PwNativeAdsDelegate_h */
