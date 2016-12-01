//
//  NativeSdkScene.hpp
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#ifndef NativeSdkScene_h
#define NativeSdkScene_h

#include "PwNativeAdsDelegate.h"
#include "BaseScene.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

class NativeSdkScene : public BaseScene, public PwNativeAdsDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    //BaseScene.h
    virtual void updateSize(const cocos2d::Size &contentSize);
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void backClicked();
    void selecteAdType(int index);
    
    //PwNativeAdsDelegate
    virtual void pwNativeAdDidFailError();
    virtual void pwNativeAdDidLoadAd();
    virtual void pwNativeAdDidPresentModal();
protected:
    cocos2d::Vector<cocos2d::CCString*>* myArray;    
private:
    int _currentType = 0;
    bool isAdsUsed = true;
    bool isAdLoading = false;
    cocos2d::ui::CheckBox* testMode;
    cocos2d::ui::EditBox* creativeIdField;
    cocos2d::ui::EditBox* zoneIdField;
    cocos2d::Label* currentNativeAd;
    
    cocos2d::ui::Button* rightButton;
    cocos2d::ui::Button* leftButton;
    
    cocos2d::ui::Button* buttonNative;
    cocos2d::ui::Button* buttonBack;
    cocos2d::Label* titleLabel;
    CREATE_FUNC(NativeSdkScene);
};

#endif /* NativeSdkScene_h */
