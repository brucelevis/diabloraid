//
//  PanelSpriteFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#include "PanelSpriteFactory.h"

PanelSprite* PanelSpriteFactory::createWithFloor(Floor* floor){
    int panelType = floor->createPanel();
    std::string panelName = ((CCString*) FieldModel::convertToPanelName(panelType))->getCString();
    
    PanelSprite* pSprite;
    if(panelName == "enemy"){
        pSprite = EnemyFactory::getEnemyPanel(floor);
    } else if(panelName == "potion"){
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "sword"){
        pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "coin"){
        pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "shield"){
        pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "kaidan"){
        pSprite = Stair::createWithSpriteFrameName(panelName.c_str());
    } else {
        pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
    }
    return pSprite;
}
