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
    LevelUpLayer *levelUpLayer = LevelUpLayer::layer();
    //push
    levelUpLayer->setCallback(events, layer);
    layer->addChild(levelUpLayer->getScene());
}