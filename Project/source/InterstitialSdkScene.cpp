//
//  InterstitialSdkScene.cpp
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#include "InterstitialSdkScene.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"

USING_NS_CC;

Scene* InterstitialSdkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InterstitialSdkScene::create();
    scene->addChild(layer,0,BASE_SCENE_TAG);
    return scene;
}

void InterstitialSdkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    CCLOG("Key pressed: %i", keyCode);
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE /*KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE)*/)
    {
        CCLOG("You pressed back button");
        //Director::getInstance()->end();
        //exit(0);
        backClicked();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_HOME)
    {
        CCLOG("You pressed home button");
        // pause the game
        backClicked();
    }
}

void InterstitialSdkScene::backClicked()
{
    if(isAdLoading == false)
    {
        CCLOG("Back Button Clicked.");
        if(isAdsUsed)
        {
            PwAdsX::sharedPwAdsX()->freeInterstitialDelegate();
        }
        Director::getInstance()->popScene();
    }
}

void InterstitialSdkScene::updateSize(const cocos2d::Size &contentSize)
{
    auto size = this->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Director::getInstance()->getOpenGLView()
    float screenWidth, screenHeight;
    //if( contentSize.width < contentSize.height)
    //{
        screenWidth = visibleSize.width;
        screenHeight = visibleSize.height;
    /*}
    else
    {
        screenHeight = visibleSize.width;
        screenWidth = visibleSize.height;
    }*/
     
    //buttonBanner
    buttonInterstitial->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonInterstitial->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //buttonBack
    buttonBack->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonBack->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
}

bool InterstitialSdkScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    setKeypadEnabled(true);
    
    PwAdsX::sharedPwAdsX()->setInterstitialDelegate(this);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    buttonInterstitial = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonInterstitial->setScale9Enabled(true);
    buttonInterstitial->setTitleText("Show Interstitial");
    buttonInterstitial->setTitleFontName("fonts/arial.ttf");
    buttonInterstitial->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonInterstitial->setPosition(Vec2(visibleSize.width / 2 + origin.x, 90 + origin.y));
    buttonInterstitial->setContentSize(cocos2d::Size(100, 50));
    buttonInterstitial->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdsUsed && isAdLoading == false)
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                bool isTestMode = true;
                PwAdsX::sharedPwAdsX()->showIntersitialAd(isTestMode);
                isAdLoading = true;
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonInterstitial, 2);    
    
    buttonBack = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonBack->setScale9Enabled(true);
    buttonBack->setTitleText("Back");
    buttonBack->setTitleFontName("fonts/arial.ttf");
    buttonBack->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonBack->setPosition(Vec2(visibleSize.width / 2 + origin.x, 30 + origin.y));
    buttonBack->setContentSize(cocos2d::Size(100, 50));
    buttonBack->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdLoading == false)
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                this->backClicked();
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonBack, 2);
    
    titleLabel = Label::createWithTTF("Interstitial Ad", "fonts/Marker Felt.ttf", 24);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);
    
    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}

void InterstitialSdkScene::pwInterstitialAdDidLoadAd()
{
	CCLOG("InterstitialSdkScene::pwInterstitialAdDidLoadAd()");
    isAdLoading = false;
}

void InterstitialSdkScene::pwInterstitialAdDidFailError()
{
	CCLOG("InterstitialSdkScene::pwInterstitialdDidFailError()");
    isAdLoading = false;
}
void InterstitialSdkScene::pwInterstitialAdDidPresentModal()
{
	CCLOG("InterstitialSdkScene::pwInterstitialAdDidPresentModal()");
}
void InterstitialSdkScene::pwInterstitialAdDidDismissModal()
{
    CCLOG("InterstitialSdkScene::pwInterstitialAdDidDismissModal()");
}