//
//  LandingPageSdkScene.cpp
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#include "LandingPageSdkScene.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"

USING_NS_CC;

Scene* LandingPageSdkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LandingPageSdkScene::create();
    scene->addChild(layer,0,BASE_SCENE_TAG);
    return scene;
}

void LandingPageSdkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void LandingPageSdkScene::backClicked()
{
    if(isAdLoading == false)
    {
        CCLOG("Back Button Clicked.");
        if(isAdsUsed)
        {
            PwAdsX::sharedPwAdsX()->freeLandingPageDelegate();
        }
        Director::getInstance()->popScene();
    }
}

void LandingPageSdkScene::updateSize(const cocos2d::Size &contentSize)
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
    //}
    //else
    //{
    //    screenHeight = visibleSize.width;
    //    screenWidth = visibleSize.height;
    //}
     
    //buttonBanner
    buttonBanner->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonBanner->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //buttonBack
    buttonBack->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonBack->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
    CCLOG("LandingPageSdkScene::updateSize end");
}

bool LandingPageSdkScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    setKeypadEnabled(true);
    
    PwAdsX::sharedPwAdsX()->setLandingPageDelegate(this);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /*
    //creative id line - start
    auto labelCreativeID = Label::createWithTTF("Creative Id", "fonts/Marker Felt.ttf", 12);
    labelCreativeID->setPosition(cocos2d::Size(180, 140));
    this->addChild(labelCreativeID, 1);
    
    creativeIdField = cocos2d::ui::EditBox::create(cocos2d::Size(100, 30), "area.png");
    creativeIdField->setFontSize(12);
    creativeIdField->setFontColor(cocos2d::Color3B(0,0,0));
    creativeIdField->setPosition(Vec2(260, 140));
    this->addChild(creativeIdField, 3);
    //creative id line - end
    
    //zone id line - start
    auto labelZoneID = Label::createWithTTF("Zone ID", "fonts/Marker Felt.ttf", 12);
    labelZoneID->setPosition(cocos2d::Size(180, 170));
    this->addChild(labelZoneID, 1);
    
    zoneIdField = cocos2d::ui::EditBox::create(cocos2d::Size(100, 30), "area.png");
    zoneIdField->setFontSize(12);
    zoneIdField->setFontColor(cocos2d::Color3B(255,0,0));
    zoneIdField->setPosition(cocos2d::Size(260, 170));
    this->addChild(zoneIdField, 3);
    //zone id line - end
     */
    /*
    //testMode checkbox line - start
    testMode = cocos2d::ui::CheckBox::create("unchecked_checkbox.png", "checked_checkbox.png", cocos2d::ui::Widget::TextureResType::LOCAL);
    testMode->setContentSize(cocos2d::Size(50, 50));
    testMode->setPosition(Vec2(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 3 + origin.y + 100));
    this->addChild(testMode, 2);
    
    auto testModeLabel = Label::createWithTTF("Test mode", "fonts/arial.ttf", 12);
    testModeLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x + 20, visibleSize.height / 3 + origin.y + 100));
    this->addChild(testModeLabel, 2);
    //testMode checkbox - end
    */
    buttonBanner = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonBanner->setScale9Enabled(true);
    buttonBanner->setTitleText("Show Landing Page");
    buttonBanner->setTitleFontName("fonts/arial.ttf");
    buttonBanner->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonBanner->setPosition(Vec2(visibleSize.width / 2 + origin.x, 90 + origin.y));
    buttonBanner->setContentSize(cocos2d::Size(visibleSize.width / 2, 50));
    buttonBanner->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdsUsed && isAdLoading == false)
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                bool isTestMode = true;
                PwAdsX::sharedPwAdsX()->showLandingPageAd(isTestMode);
                isAdLoading = true;
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonBanner, 2);
        
    buttonBack = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonBack->setScale9Enabled(true);
    buttonBack->setTitleText("Back");
    buttonBack->setTitleFontName("fonts/arial.ttf");
    buttonBack->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonBack->setPosition(Vec2(visibleSize.width / 2 + origin.x, 30 + origin.y));
    buttonBack->setContentSize(cocos2d::Size(visibleSize.width / 2, 50));
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
    
    titleLabel = Label::createWithTTF("Landing Page Ad", "fonts/Marker Felt.ttf", 24);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);
    
    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}


void LandingPageSdkScene::pwLandingPageAdDidLoadAd()
{
    CCLOG("LandingPageSdkScene::pwLandingPageAdDidLoadAd");
    isAdLoading = false;
}
void LandingPageSdkScene::pwLandingPageAdDidFailError()
{
    CCLOG("LandingPageSdkScene::pwLandingPageAdDidLoadAd");
    isAdLoading = false;
}
void LandingPageSdkScene::pwLandingPageAdDidPresentModal()
{
    CCLOG("LandingPageSdkScene::pwLandingPageAdDidPresentModal");
}