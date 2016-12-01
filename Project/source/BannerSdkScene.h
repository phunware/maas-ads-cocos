//
//  BannerSdkScene.h
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#ifndef BannerSdkScene_h
#define BannerSdkScene_h

#include "PwAdsX.h"
#include "PwBannerAdsDelegate.h"
#include "BaseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class BannerSdkScene : public BaseScene, public PwBannerAdsDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //BaseScene.h
    virtual void updateSize(const cocos2d::Size &contentSize);
    
    //virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    
    //PwVideoInterstitialAdsDelegate
    virtual void pwBannerAdDidFailError();
    virtual void pwBannerAdDidLoadAd();
    virtual void pwBannerAdDidPresentModal();
    
private:
    bool isAdsUsed = true;
    bool isAdLoading = false;
    cocos2d::ui::CheckBox* checkBox;
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::EditBox* creativeIdField;
    cocos2d::ui::EditBox* zoneIdField;
    
    cocos2d::ui::Button* buttonBanner;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    cocos2d::Label* checkBoxLabel;
    // implement the "static create()" method manually
    CREATE_FUNC(BannerSdkScene);
};

#endif /* BannerSdkScene_h */
