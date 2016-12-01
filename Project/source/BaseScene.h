//
//  BaseScene.h
//  No Ads Phunware
//
//  Created by Admin on 10/24/16.
//
//

#ifndef BaseScene_h
#define BaseScene_h

#define BASE_SCENE_TAG 999

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "PwAdsX.h"

class BaseScene : public cocos2d::Layer
{
public:
    
    virtual void updateSize(const cocos2d::Size &contentSize);

};

#endif /* BaseScene_h */
