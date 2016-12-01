//
//  NativeSdkScene.cpp
//  PhunwarePluginCocos
//
//  Created by Sergey on 8/3/16.
//
//

#include "NativeSdkScene.h"
#include "PwAdsX.h"

USING_NS_CC;

Scene* NativeSdkScene::createScene()
{    
    //myArray = new Vector <CCString*>();
    //CCString* dataString = new CCString("myString");
    //myArray->pushBack(dataString);
    
    auto scene = Scene::create();
    auto layer = NativeSdkScene::create();
    scene->addChild(layer,0,BASE_SCENE_TAG);
    return scene;
}


void NativeSdkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void NativeSdkScene::selecteAdType(int index)
{
    int itemsNumber = myArray->size();
    _currentType = (_currentType + itemsNumber + index) % itemsNumber;
    
    currentNativeAd->setString(std::string(myArray->at(_currentType)->_string));
}

void NativeSdkScene::backClicked()
{
    if(isAdLoading == false)
    {
        CCLOG("Back Button Clicked.");
        if(isAdsUsed)
        {
            PwAdsX::sharedPwAdsX()->freeNativeDelegate();
            PwAdsX::sharedPwAdsX()->hideNativeAd();
        }
        Director::getInstance()->popScene();
    }
}


void NativeSdkScene::updateSize(const cocos2d::Size &contentSize)
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
    
    //buttonNative
    buttonNative->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonNative->setContentSize(cocos2d::Size(screenWidth / 2 , screenHeight / 8));
    
    //buttonBack
    buttonBack->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonBack->setContentSize(cocos2d::Size(screenWidth / 2 , screenHeight / 8));
    
    
    leftButton->setPosition(Vec2(screenWidth / 3 + origin.x, screenHeight * 5 / 8 ));
    rightButton->setPosition(Vec2(screenWidth * 2 / 3 + origin.x, screenHeight * 5 / 8 ));
    currentNativeAd->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 5 / 8 ));
    
    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
}

bool NativeSdkScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    setKeypadEnabled(true);
    
    PwAdsX::sharedPwAdsX()->setNativeDelegate(this);
    
    myArray = new Vector <CCString*>();
    CCString* dataString = new CCString("News Feed");
    myArray->pushBack(dataString);
    dataString = new CCString("App Wall");
    myArray->pushBack(dataString);
    dataString = new CCString("Content Wall");
    myArray->pushBack(dataString);
    dataString = new CCString("Content Stream");
    myArray->pushBack(dataString);
    dataString = new CCString("Clean");
    myArray->pushBack(dataString);
    dataString = new CCString("3Up");
    myArray->pushBack(dataString);
    dataString = new CCString("3UpWith2Ads");
    myArray->pushBack(dataString);
    dataString = new CCString("3UpWith1Ad");
    myArray->pushBack(dataString);
    dataString = new CCString("Single Icon");
    myArray->pushBack(dataString);
    dataString = new CCString("Multi Icon");
    myArray->pushBack(dataString);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    
    // Native ad type select - start
    currentNativeAd = Label::createWithTTF("Native Ad", "fonts/Marker Felt.ttf", 12);
    currentNativeAd->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      visibleSize.height / 3 + origin.y + 150));
    currentNativeAd->setString(std::string(myArray->at(_currentType)->_string));
    this->addChild(currentNativeAd, 1);
    
    rightButton = cocos2d::ui::Button::create("arrow_right.png", "arrow_right.png", "arrow_right.png");
    rightButton->setTitleFontName("fonts/arial.ttf");
    rightButton->setTitleColor(cocos2d::Color3B(0,0,0));
    rightButton->setContentSize(cocos2d::Size(32, 32));
    rightButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 65, visibleSize.height / 3 + origin.y + 150));
    rightButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdLoading == false)
            switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCLOG("Switch to right");
                this->selecteAdType(1);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(rightButton, 2);
    
    leftButton = cocos2d::ui::Button::create("arrow_left.png", "arrow_left.png", "arrow_left.png");
    leftButton->setTitleFontName("fonts/arial.ttf");
    leftButton->setTitleColor(cocos2d::Color3B(0,0,0));
    leftButton->setContentSize(cocos2d::Size(32, 32));
    leftButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 65, visibleSize.height / 3 + origin.y + 150));
    leftButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdLoading == false)
            switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCLOG("Switch to left");
                this->selecteAdType(-1);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(leftButton, 2);
    // Native ad type select - end
    
    buttonNative = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonNative->setScale9Enabled(true);
    buttonNative->setTitleText("Show Native");
	buttonNative->setTitleFontName("fonts/arial.ttf");
    buttonNative->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonNative->setPosition(Vec2(visibleSize.width / 2 + origin.x, 90 + origin.y));
    buttonNative->setContentSize(cocos2d::Size(100, 50));
    buttonNative->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdsUsed && isAdLoading == false)
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                bool isTestMode = true;
                PwAdsX::sharedPwAdsX()->showNativeAd(myArray->at(_currentType)->_string.c_str(), isTestMode);
                isAdLoading = true;
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonNative, 2);    
        
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
    
    
    titleLabel = Label::createWithTTF("Native Ad", "fonts/Marker Felt.ttf", 24);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);
    
    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}

void NativeSdkScene::pwNativeAdDidFailError()
{
    CCLOG("NativeSdkScene::pwNativeAdDidFailError");
    isAdLoading = false;
}

void NativeSdkScene::pwNativeAdDidLoadAd()
{
    CCLOG("NativeSdkScene::pwNativeAdDidLoadAd");
    isAdLoading = false;    
}

void NativeSdkScene::pwNativeAdDidPresentModal()
{
    CCLOG("NativeSdkScene::pwNativeAdDidPresentModal");
}