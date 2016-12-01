#ifndef __MasterScene_H__
#define __MasterScene_H__

#include "cocos2d.h"
#include "BaseScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"

#include "BannerSdkScene.h"
#include "InterstitialSdkScene.h"
#include "VideoInterstitialSdkScene.h"
#include "LandingPageSdkScene.h"
#include "NativeSdkScene.h"
#include "RewardedVideoSdkScene.h"

class MasterScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    virtual void updateSize(const cocos2d::Size &contentSize);
    
    virtual void setContentSize(const cocos2d::Size &contentSize);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MasterScene);
protected:
    cocos2d::ui::Button* buttonInterstittial;
    cocos2d::ui::Button* buttonVideoInterstittial;
    cocos2d::ui::Button* buttonRewardedVideo;
    cocos2d::ui::Button* buttonBanner;
    cocos2d::ui::Button* buttonNative;
    cocos2d::ui::Button* buttonLandingPage;
    cocos2d::Label* titleLabel;
};

#endif // __MasterScene_H__
