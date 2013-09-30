//
//  Events.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#include "Events.h"

void Events::handle(CCLayer* layer){
    EventBase* event;
    // 0になったら何もしない。
    if (!this || !this->count()){
        return;
    }
    CCLOG("Events::handle : remainings: %d", this->count());
    event = (EventBase*) this->objectAtIndex(0);
    this->removeObjectAtIndex(0);
    event->action(this, layer);
}