//
//  RewardedVideoSdkScene.h
//  No Ads Phunware
//
//  Created by Admin on 10/24/16.
//
//

#ifndef RewardedVideoSdkScene_h
#define RewardedVideoSdkScene_h

#include "PwRewardedVideoAdsDelegate.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseScene.h"


class RewardedVideoSdkScene: public BaseScene, public PwRewardedVideoAdsDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //BaseScene.h
    virtual void updateSize(const cocos2d::Size &contentSize);

    void ShowRewardedVideoDialog();
    void ShowRewardedVideoResultsDialog(bool succeeded, int errorCode);
    void SetDataFromString(std::string);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    void OnDialogOKButtonPressed(Ref *sender);

    //PwRewardedVideoAdsDelegate
    virtual void pwRewardedVideoAdDidFailError(std::string rvData);
    virtual void pwRewardedVideoAdDidLoadAd(std::string rvData);
    virtual void pwRewardedVideoAdDidDismissModal(std::string rvData);
    virtual void pwRewardedVideoAdDidSucceed(std::string rvData);

private:
    bool isAdsUsed = true;
    bool isAdLoading = false;
    std::string _userId;
    int _rewardAmount;
    std::string _currencyId;
    int _remainingViews;
    int _errorCode;
    bool receivedRVSuccess;
    
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::Button* buttonRewardedVideo;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    cocos2d::ui::Layout* rewardedVideoDialog;
    cocos2d::Label* dialogBody;
    cocos2d::ui::Button* dialogButton;
    
    CREATE_FUNC(RewardedVideoSdkScene);
};
#endif /* RewardedVideoSdkScene_h */
