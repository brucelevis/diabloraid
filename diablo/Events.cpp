//
//  Events.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#include "Events.h"
CCArray* Events::create(){
    CCArray* pArray = (CCArray*) new Events();
  
    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

void Events::handle(CCLayer* layer){
       EventBase* event;
    // 0になったら何もしない。
    if (!this || !this->count()){
        return;
    }
    if( _handling ) {
        //処理中の時は何もしない。
        return;
    }
    this->setHandling(true);
    CCLOG("Events::handle : remainings: %d", this->count());
    event = (EventBase*) this->objectAtIndex(0);
    this->removeObjectAtIndex(0);
    event->action(this, layer);
}

void Events::setHandling(bool handling){
    this->_handling = handling;
}

Events::Events(){
    _handling = false;
}

Events::~Events(){
}
