//
//  LevelUpLayer.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/20.
//
//

#ifndef __diablo__LevelUpLayer__
#define __diablo__LevelUpLayer__

#include <iostream>
#include "cocos2d.h"
#include "StatusUpgrade.h"

using namespace cocos2d;
class LevelUpLayer : public CCLayer{
    CCArray* status;
    CCLabelTTF* remainings;
    StatusUpgrade *strength, *defense, *dexterity, *vitality;
    CCMenuItemSprite* pOkButton;
    int remain;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    void update();
    void close();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    CREATE_FUNC(LevelUpLayer);
};

#endif /* defined(__diablo__LevelUpLayer__) */
