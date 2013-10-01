//
//  LevelUpEvent.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#ifndef __diablo__LevelUpEvent__
#define __diablo__LevelUpEvent__

#include <iostream>
#include "EventBase.h"
#include "Events.h"
#include "LevelUpLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

class LevelUpEvent : public EventBase {
    virtual void action(Events* events, CCLayer* layer);
};

#endif /* defined(__diablo__LevelUpEvent__) */