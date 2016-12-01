//
//  InterstitialSdkScene.h
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#ifndef InterstitialSdkScene_h
#define InterstitialSdkScene_h

#include "PwInterstitialAdsDelegate.h"
#include "BaseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InterstitialSdkScene : public BaseScene, public PwInterstitialAdsDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //BaseScene.h
    virtual void updateSize(const cocos2d::Size &contentSize);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    
    //PwInterstitialAdsDelegate
    virtual void pwInterstitialAdDidLoadAd();
    virtual void pwInterstitialAdDidFailError();
    //virtual void pwInterstitialdDidFailError();
    virtual void pwInterstitialAdDidDismissModal();
    virtual void pwInterstitialAdDidPresentModal();
    
private:
    bool isAdsUsed = true;
    bool isAdLoading = false;
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::EditBox* creativeIdField;
    cocos2d::ui::EditBox* zoneIdField;
    
    cocos2d::ui::Button* buttonInterstitial;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    CREATE_FUNC(InterstitialSdkScene);
};

#endif /* InterstitialSdkScene_h */
