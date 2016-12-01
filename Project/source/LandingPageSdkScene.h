//
//  LandingPageSdkScene.h
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#ifndef LandingPageSdkScene_h
#define LandingPageSdkScene_h

#include "PwLandingPageAdsDelegate.h"
#include "BaseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LandingPageSdkScene : public BaseScene, public PwLandingPageAdsDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //BaseScene.h
    virtual void updateSize(const cocos2d::Size &contentSize);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    
    //PwVideoInterstitialAdsDelegate
    virtual void pwLandingPageAdDidLoadAd();
    virtual void pwLandingPageAdDidFailError();
    virtual void pwLandingPageAdDidPresentModal();
    
private:
    bool isAdsUsed = true;
    bool isAdLoading = false;
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::EditBox* creativeIdField;
    cocos2d::ui::EditBox* zoneIdField;
    
    cocos2d::ui::Button* buttonBanner;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    CREATE_FUNC(LandingPageSdkScene);
};

#endif /* LandingPageSdkScene_h */
