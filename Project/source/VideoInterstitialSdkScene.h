//
//  VideoInterstitialSdkScene.h
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#ifndef VideoInterstitialSdkScene_h
#define VideoInterstitialSdkScene_h

#include "PwVideoInterstitialAdsDelegate.h"
#include "BaseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class VideoInterstitialSdkScene : public BaseScene, public PwVideoInterstitialAdsDelegate
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
    virtual void pwVideoInterstitialAdDidLoadAd();
    virtual void pwVideoInterstitialAdDidFailError();
    virtual void pwVideoInterstitialAdDidPresentModal();
    
private:
    bool isAdsUsed = true;
    bool isAdLoading = false;
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::EditBox* creativeIdField;
    cocos2d::ui::EditBox* zoneIdField;
    
    cocos2d::ui::Button* buttonVideoInterstitial;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    CREATE_FUNC(VideoInterstitialSdkScene);
};

#endif /* VideoInterstitialSdkScene_h */
