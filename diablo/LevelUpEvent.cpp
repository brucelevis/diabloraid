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
    //LevelUpLayer *levelUpLayer = LevelUpLayer::layerWithAttributes(_player->getAttributes());
    LevelUpLayer *levelUpLayer = LevelUpLayer::layerWithPlayer(_player);
    //push
    levelUpLayer->setCallback(events, layer);
    layer->addChild(levelUpLayer->getScene());
}

void LevelUpEvent::onEnd(){
}


LevelUpEvent::LevelUpEvent(Player* player) : EventBase(player){
}

LevelUpEvent::~LevelUpEvent(){
}