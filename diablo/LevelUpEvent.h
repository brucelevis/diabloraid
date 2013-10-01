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
#include "Attributes.h"
#include "Player.h"
using namespace CocosDenshion;
using namespace cocos2d;

class LevelUpEvent : public EventBase {
public:
    virtual void action(Events* events, CCLayer* layer);
    LevelUpEvent(Player* player);
    ~LevelUpEvent();
};

#endif /* defined(__diablo__LevelUpEvent__) */