//
//  EventFactory.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__EventFactory__
#define __diablo__EventFactory__

#include <iostream>
#include "EventBase.h"
#include "LevelUpEvent.h"
#include "Player.h"

class EventFactory{
public:
    static EventBase* create(int type, Player* player);
};

#endif /* defined(__diablo__EventFactory__) */
