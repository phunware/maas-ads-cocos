//
//  PwRewardedVideoAdsDelegate.h
//  TestCocos
//
//  Created by Sergey on 8/1/16.
//
//

#ifndef PwRewardedVideoAdsDelegate_h
#define PwRewardedVideoAdsDelegate_h
#include <string>

class PwRewardedVideoAdsDelegate {
public:
    virtual ~PwRewardedVideoAdsDelegate() {}
    
    virtual void pwRewardedVideoAdDidFailError(std::string rvData){}
    virtual void pwRewardedVideoAdDidLoadAd(std::string rvData){}
    virtual void pwRewardedVideoAdDidDismissModal(std::string rvData){}
    virtual void pwRewardedVideoAdDidSucceed(std::string rvData){}
};
#endif /* PwRewardedVideoAdsDelegate_h */
