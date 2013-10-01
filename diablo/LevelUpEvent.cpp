//
//  LevelUpEvent.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#include "LevelUpEvent.h"

void LevelUpEvent::action(Events* events, CCLayer* layer){
    CCLOG("LevelUpEvent::action");
    SimpleAudioEngine::sharedEngine()->playEffect("levelup.wav");
    LevelUpLayer *levelUpLayer = LevelUpLayer::layerWithAttributes(_player->getAttributes());
    //push
    levelUpLayer->setCallback(events, layer);
    layer->addChild(levelUpLayer->getScene());
}

LevelUpEvent::LevelUpEvent(Player* player) : EventBase(player){
}

LevelUpEvent::~LevelUpEvent(){
}