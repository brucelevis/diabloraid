//
//  EventBase.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#include "EventBase.h"
#include "Events.h"

void EventBase::action(Events *events, CCLayer* layer){
    CCLOG("EventBase::action");
}

void EventBase::onEnd(){
}

EventBase::EventBase(Player* player){
    _player = player;
}

EventBase::EventBase(){
}

EventBase::~EventBase(){
}

