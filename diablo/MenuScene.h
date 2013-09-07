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
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
};

#endif /* defined(__diablo__MenuScene__) */
