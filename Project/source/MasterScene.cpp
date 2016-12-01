#include "MasterScene.h"

USING_NS_CC;

Scene* MasterScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MasterScene::create();
    scene->setonEnterTransitionDidFinishCallback([&](){
        CCLOG("Scene callback!");
        if(layer != nullptr)
        {
            //int newWidth;
            //int newHeight;
            Scene* currentScene = Director::sharedDirector()->getRunningScene();
            
            auto layer = currentScene->getChildByTag(999);
            if(layer != nullptr)
            {
                ((BaseScene*)layer)->updateSize(Director::getInstance()->getVisibleSize());
            }
        }
    });

    // add layer as a child to scene
    scene->addChild(layer,0,BASE_SCENE_TAG);

    // return the scene
    return scene;
}

void MasterScene::setContentSize(const cocos2d::Size &contentSize)
{
    Node::setContentSize(contentSize);
}

void MasterScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE /*KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE)*/)
    {
        backClicked();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_HOME)
    {
        backClicked();
    }
}

void MasterScene::backClicked()
{
    Director::getInstance()->end();
}

void MasterScene::updateSize(const cocos2d::Size &contentSize)
{
    auto size = this->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->setContentSize(visibleSize);
    size = this->getContentSize();
    //Director::getInstance()->getOpenGLView()
    float screenWidth, screenHeight;
    if( contentSize.width < contentSize.height)
    {
        screenWidth = visibleSize.width;
        screenHeight = visibleSize.height;
    }
    else
    {
        screenWidth = visibleSize.width;
        screenHeight = visibleSize.height;
        
        //screenHeight = visibleSize.width;
        //screenWidth = visibleSize.height;
    }
    
    //video button
    buttonVideoInterstittial->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 5 / 8 ));
    buttonVideoInterstittial->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //interstitial button
    buttonInterstittial->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 4 / 8 ));
    buttonInterstittial->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //buttonBanner
    buttonBanner->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 3 / 8 ));
    buttonBanner->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //buttonNative
    buttonNative->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 2 / 8 ));
    buttonNative->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //buttonLandingPage
    buttonLandingPage->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 1 / 8 ));
    buttonLandingPage->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    //rewarded video button
    buttonRewardedVideo->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 6 / 8 ));
    buttonRewardedVideo->setContentSize(cocos2d::Size(screenWidth / 2, screenHeight / 8));
    
    //titleLabel
    titleLabel->setPosition(Vec2(screenWidth / 2 + origin.x, screenHeight * 7 / 8 ));
    //titleLabel->set
}

// on "init" you need to initialize your instance
bool MasterScene::init()
{
	PwAdsX::sharedPwAdsX();
    
    if ( !Layer::init() )
    {
        return false;
    }    
    
    //Init back button handler
    setKeypadEnabled(true);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonInterstittial = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonInterstittial->setTitleText("Interstitial");
    buttonInterstittial->setTitleFontName("fonts/arial.ttf");
    buttonInterstittial->setScale9Enabled(true);
    buttonInterstittial->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonInterstittial->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 5 / 6 + origin.y - 25));
    buttonInterstittial->setContentSize(cocos2d::Size(120, 30));
    buttonInterstittial->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto interstitialScene = InterstitialSdkScene::createScene();
                Director::getInstance()->pushScene(interstitialScene);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonInterstittial, 2);
    
    buttonVideoInterstittial = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonVideoInterstittial->setTitleText("Video Interstitial");
    buttonVideoInterstittial->setTitleFontName("fonts/arial.ttf");
    buttonVideoInterstittial->setScale9Enabled(true);
    buttonVideoInterstittial->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonVideoInterstittial->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 5 / 7 + origin.y - 20));
    buttonVideoInterstittial->setContentSize(cocos2d::Size(120, 40));
    buttonVideoInterstittial->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                {
                    auto videoScene = VideoInterstitialSdkScene::createScene();
                    Director::getInstance()->pushScene(videoScene);
                    //auto videoRewardedScene = RewardedVideoSdkScene::createScene();
                    //Director::getInstance()->pushScene(videoRewardedScene);
                }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonVideoInterstittial, 2);
    
    
    buttonRewardedVideo = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonRewardedVideo->setTitleText("Rewarded Video");
    buttonRewardedVideo->setTitleFontName("fonts/arial.ttf");
    buttonRewardedVideo->setScale9Enabled(true);
    buttonRewardedVideo->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonRewardedVideo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 4 / 7 + origin.y - 20));
    buttonRewardedVideo->setContentSize(cocos2d::Size(120, 40));
    buttonRewardedVideo->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                //auto videoScene = VideoInterstitialSdkScene::createScene();
                //Director::getInstance()->pushScene(videoScene);
                auto videoRewardedScene = RewardedVideoSdkScene::createScene();
                Director::getInstance()->pushScene(videoRewardedScene);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonRewardedVideo, 2);
    
    
    buttonBanner = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonBanner->setTitleText("Banner");
    buttonBanner->setTitleFontName("fonts/arial.ttf");
    buttonBanner->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonBanner->setScale9Enabled(true);
    buttonBanner->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 7 + origin.y - 20));
    buttonBanner->setContentSize(cocos2d::Size(120, 40));
    buttonBanner->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto bannerScene = BannerSdkScene::createScene();
                Director::getInstance()->pushScene(bannerScene);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonBanner, 2);
    
    
    buttonNative = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonNative->setTitleText("Native");
    buttonNative->setTitleFontName("fonts/arial.ttf");
    buttonNative->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonNative->setScale9Enabled(true);
    buttonNative->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 2 / 7 + origin.y - 20));
    buttonNative->setContentSize(cocos2d::Size(120, 40));
    buttonNative->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto nativeScene = NativeSdkScene::createScene();
                Director::getInstance()->pushScene(nativeScene);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonNative, 2);
    
    buttonLandingPage = cocos2d::ui::Button::create("area.png", "area.png", "area.png");
    buttonLandingPage->setTitleText("Landing Page");
    buttonLandingPage->setTitleFontName("fonts/arial.ttf");
    buttonLandingPage->setTitleColor(cocos2d::Color3B(0,0,0));
    buttonLandingPage->setScale9Enabled(true);
    buttonLandingPage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 7 + origin.y - 20));
    buttonLandingPage->setContentSize(cocos2d::Size(120, 40));
    buttonLandingPage->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                auto landingPageScene = LandingPageSdkScene::createScene();
                Director::getInstance()->pushScene(landingPageScene);
            }
                break;
            default:
                break;
        }
    });
    this->addChild(buttonLandingPage, 2);
    
    
    titleLabel = Label::createWithTTF("Cocos Plugin Example", "fonts/Marker Felt.ttf", 20);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 1);

    this->updateSize(Director::getInstance()->getVisibleSize());
    
    return true;
}

void MasterScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
}
