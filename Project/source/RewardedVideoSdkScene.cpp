//
//  RewardedVideoSdkScene.cpp
//  No Ads Phunware
//
//  Created by Admin on 10/24/16.
//
//

#include "RewardedVideoSdkScene.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"
#include "JSONParse.h"
#include "JSONValue.h"

USING_NS_CC;

Scene* RewardedVideoSdkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = RewardedVideoSdkScene::create();
    scene->addChild(layer,0,BASE_SCENE_TAG);
    return scene;
}

void RewardedVideoSdkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void RewardedVideoSdkScene::backClicked()
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

void RewardedVideoSdkScene::updateSize(const cocos2d::Size &contentSize)
{
    //auto size = this->getContentSize();
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
    buttonRewardedVideo->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonRewardedVideo->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //interstitial button
    buttonBack->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonBack->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
}

bool RewardedVideoSdkScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    _userId = "CocosDude";
    PwAdsX::sharedPwAdsX()->setRewardedVideoDelegate(this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonRewardedVideo = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonRewardedVideo->setScale9Enabled(true);
    buttonRewardedVideo->setTitleText("Show Rewarded Video");
    buttonRewardedVideo->setTitleFontName("fonts/arial.ttf");
    buttonRewardedVideo->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonRewardedVideo->setPosition(Vec2(visibleSize.width / 2 + origin.x, 90 + origin.y));
    buttonRewardedVideo->setContentSize(cocos2d::Size(100, 50));
    buttonRewardedVideo->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(isAdsUsed && isAdLoading == false)
            switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                bool isTestMode = false;
                const char *zone = "78817";
                //const char *zone = "78393";

                PwAdsX::sharedPwAdsX()->loadRewardedVideoAd(isTestMode, zone, "", _userId.c_str());
                isAdLoading = true;
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonRewardedVideo, 2);
    buttonRewardedVideo->setTitleFontSize(8);


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
    
    titleLabel = Label::createWithTTF("Rewarded Video Ad", "fonts/Marker Felt.ttf", 20);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);
    
    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}

void RewardedVideoSdkScene::ShowRewardedVideoDialog()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const std::string bodyText = _userId + ", you have " + std::to_string(_remainingViews) + " remaining Rewarded Video viewings.\n Press OK to watch a Rewarded Video.";
    const float dialogWidth = 400.0f;
    const float dialogHeight = 300.0f;
    rewardedVideoDialog = ui::Layout::create();
    rewardedVideoDialog->setContentSize(Size(dialogWidth, dialogHeight));
    rewardedVideoDialog->setPosition(Vec2(visibleSize.width/2.0f + origin.x - dialogWidth/2, visibleSize.height/1.5f + origin.y - dialogHeight/2));
    rewardedVideoDialog->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    rewardedVideoDialog->setBackGroundColor(Color3B(63,127,255));

    Label *dialogHeader = Label::createWithTTF("RV Dialog Header", "fonts/arial.ttf", 28, Size(400, 32), TextHAlignment::CENTER);
    dialogBody = Label::createWithTTF(bodyText, "fonts/arial.ttf", 24, Size(400, 200), TextHAlignment::CENTER);
    dialogButton = ui::Button::create("button_normal.png", "button_pressed.png");
    ui::Button* cancelButton = ui::Button::create("xbutton_normal.png", "xbutton_pressed.png");

    dialogHeader->setTextColor(Color4B(0,0,0,255));
    dialogBody->setTextColor(Color4B(0,0,0,255));
    dialogHeader->setTextColor(Color4B(0,0,0,255));

    dialogButton->setTitleFontSize(20.0f);
    dialogButton->setTitleText("OK");
    dialogButton->addClickEventListener(CC_CALLBACK_1(RewardedVideoSdkScene::OnDialogOKButtonPressed, this));

    cancelButton->setScale(3.0f);
    cancelButton->addClickEventListener([=](Ref *sender){
        CC_UNUSED_PARAM(sender);
        this->removeChild(rewardedVideoDialog);
    });

    rewardedVideoDialog->addChild(dialogHeader, 2);
    rewardedVideoDialog->addChild(dialogBody, 3);
    rewardedVideoDialog->addChild(dialogButton, 4);
    rewardedVideoDialog->addChild(cancelButton, 5);

    dialogHeader->setPosition(Vec2(dialogWidth/2 + origin.x, 280.0f));
    dialogBody->setPosition(Vec2(dialogWidth/2 + origin.x, 150));
    dialogButton->setPosition(Vec2(dialogWidth/2 + origin.x, 30));
    cancelButton->setPosition(Vec2(dialogWidth, dialogHeight));

    this->addChild(rewardedVideoDialog);
}

void RewardedVideoSdkScene::ShowRewardedVideoResultsDialog(bool succeeded, int errorCode)
{
    CCLOG("RewardedVideoSdkScene::ShowRewardedVideoResultsDialog...");
    if (succeeded && errorCode == 0)
    {
        dialogBody->setString(_userId + " contratulations!\nYou have earned " + std::to_string(_rewardAmount) + " " + _currencyId);
    }
    else
    {
        switch(errorCode)
        {
            case 554:
                if(dialogBody != nullptr) dialogBody->setString("Unexpected time delta detected.\nPlay duration did not reach required length!");
                break;
            case 557:
                if(dialogBody != nullptr) dialogBody->setString(_userId + " You have no more remaining Rewarded Video viewings.\nCome back later to watch more Rewarded Videos.");
                break;
            default:
                if(dialogBody != nullptr) dialogBody->setString("Unsupported Error.\nRewarded Video viewing aborted.");
                return;
        }
    }
    dialogButton->addClickEventListener([=](Ref *sender){
        CC_UNUSED_PARAM(sender);
        this->removeChild(rewardedVideoDialog);
    });
}

void RewardedVideoSdkScene::OnDialogOKButtonPressed(Ref *sender)
{
    CCLOG(" RewardedVideoSdkScene::OnDialogOKButtonPressed....");
    bool isTestMode = false;
    receivedRVSuccess = false;
    PwAdsX::sharedPwAdsX()->showRewardedVideoAd(isTestMode);
}

void RewardedVideoSdkScene::pwRewardedVideoAdDidFailError(std::string rvData)
{
    CCLOG(" RewardedVideoSdkScene::pwRewardedVideoAdDidFailError");
    isAdLoading = false;
    SetDataFromString(rvData);
    ShowRewardedVideoResultsDialog(false, _errorCode);
}

void RewardedVideoSdkScene::pwRewardedVideoAdDidLoadAd(std::string rvData)
{
    CCLOG(" RewardedVideoSdkScene::pwRewardedVideoAdDidLoadAd");
    isAdLoading = false;
    SetDataFromString(rvData);
    ShowRewardedVideoDialog();
}

void RewardedVideoSdkScene::pwRewardedVideoAdDidDismissModal(std::string rvData)
{
    CCLOG(" RewardedVideoSdkScene::pwRewardedVideoAdDidPresentModal");
    isAdLoading = false;

    // if we already got the RVSuccess event, we're done with this viewing
    if (receivedRVSuccess) return;

    SetDataFromString(rvData);

    if (_errorCode == 0) return;

    ShowRewardedVideoResultsDialog(false, _errorCode);
}

void RewardedVideoSdkScene::pwRewardedVideoAdDidSucceed(std::string rvData)
{
    CCLOG(" RewardedVideoSdkScene::pwRewardedVideoAdDidSucceed");
    receivedRVSuccess = true;
    isAdLoading = false;
    SetDataFromString(rvData);
    ShowRewardedVideoResultsDialog(true, 0);
}

void RewardedVideoSdkScene::SetDataFromString(std::string dataString)
{
    CCLOG("RewardedVideoSdkScene::SetDataFromString: dataString=%s", dataString.c_str());
    JSONValue *value = JSON::Parse(dataString.c_str());
    value->GetInt(L"remainingViews", &_remainingViews);
    value->GetInt(L"rewardAmount", &_rewardAmount);
    value->GetString(L"currencyId", &_currencyId);
    value->GetInt(L"errorCode", &_errorCode);
    CCLOG("RewardedVideoSdkScene::SetDataFromString: dataString Parsed - _rewardAmount=%d, _currencyId=%s, _remainingViews=%d", _rewardAmount, _currencyId.c_str(), _remainingViews);
}
