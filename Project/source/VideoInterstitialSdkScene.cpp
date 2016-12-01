//
//  VideoInterstitialSdkScene.cpp
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#include "VideoInterstitialSdkScene.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"

USING_NS_CC;

Scene* VideoInterstitialSdkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = VideoInterstitialSdkScene::create();
    scene->addChild(layer,0,BASE_SCENE_TAG);
    return scene;
}

void VideoInterstitialSdkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void VideoInterstitialSdkScene::backClicked()
{
    if(isAdLoading == false)
    {
        CCLOG("Back Button Clicked.");
        if(isAdsUsed)
        {
            PwAdsX::sharedPwAdsX()->freeVideoDelegate();
        }
        Director::getInstance()->popScene();
    }
}

void VideoInterstitialSdkScene::updateSize(const cocos2d::Size &contentSize)
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
    
    
    //video button
    buttonVideoInterstitial->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonVideoInterstitial->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //interstitial button
    buttonBack->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonBack->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));

    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
}

bool VideoInterstitialSdkScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    setKeypadEnabled(true);
    
    PwAdsX::sharedPwAdsX()->setVideoDelegate(this);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonVideoInterstitial = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonVideoInterstitial->setScale9Enabled(true);
    buttonVideoInterstitial->setTitleText("Show Video Interstitial");
    buttonVideoInterstitial->setTitleFontName("fonts/arial.ttf");
    buttonVideoInterstitial->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonVideoInterstitial->setPosition(Vec2(visibleSize.width / 2 + origin.x, 90 + origin.y));
    buttonVideoInterstitial->setContentSize(cocos2d::Size(100, 50));
    buttonVideoInterstitial->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdsUsed && isAdLoading == false)
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                bool isTestMode = true;
                PwAdsX::sharedPwAdsX()->showVideoIntersitialAd(isTestMode);
                isAdLoading = true;
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonVideoInterstitial, 2);
    buttonVideoInterstitial->setTitleFontSize(8);
    
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
    buttonBack->setTitleFontSize(8);
    
    titleLabel = Label::createWithTTF("Video Interstitial Ad", "fonts/Marker Felt.ttf", 20);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);
    
    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}

void VideoInterstitialSdkScene::pwVideoInterstitialAdDidFailError()
{
    CCLOG("VideoInterstitialSdkScene::pwVideoInterstitialAdDidFailError");
    isAdLoading = false;
}

void VideoInterstitialSdkScene::pwVideoInterstitialAdDidLoadAd()
{
    CCLOG("VideoInterstitialSdkScene::pwVideoInterstitialAdDidLoadAd");
    isAdLoading = false;
}

void VideoInterstitialSdkScene::pwVideoInterstitialAdDidPresentModal()
{
    CCLOG("VideoInterstitialSdkScene::pwVideoInterstitialAdDidPresentModal");
}