//
//  EventFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "EventFactory.h"

EventBase* EventFactory::create(int type, Player* player){
    switch (type) {
        case 1:
            return new LevelUpEvent(player);
            break;
        default:
            return NULL;
            break;
    }
}