//
//  MenuScene.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/07.
//
//

#ifndef __diablo__MenuScene__
#define __diablo__MenuScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public cocos2d::CCLayer
{
    CCLabelTTF* gameMainLabel;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void gameMainAction();
    CREATE_FUNC(MenuScene);
};

#endif /* defined(__diablo__MenuScene__) */
