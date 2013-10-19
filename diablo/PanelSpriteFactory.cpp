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
    int type; //とりま。
    int typeInstanceId; //とりま。
    if(panelName == "enemy"){
        type = 1;
        EnemyData* enemy = EnemyFactory::createEnemy(floor);
        typeInstanceId = enemy->getId();
        pSprite = Enemy::createWithEnemyMaster(enemy->master);
    } else if(panelName == "potion"){
        type = 4;
        typeInstanceId = 0;
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "sword"){
        type = 3;
        typeInstanceId = 0;
        pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "coin"){
        type = 0;
        typeInstanceId = 0;
        pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "shield"){
        type = 2;
        typeInstanceId = 0;
        pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "kaidan"){
        type = 5;
        typeInstanceId = 0;
        pSprite = Stair::createWithSpriteFrameName(panelName.c_str());
    } else {
        type = -1;
        typeInstanceId = 0;
        pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
    }
    PanelData* panelData = PanelData::create(type, typeInstanceId);
    CCLOG("panelData: id:%d, type: %d, typeInstanceId: %d", panelData->getId(), panelData->getType(), panelData->getTypeInstanceId());
    //そもそもpanelDataから生成するようにしたいところ
    pSprite->setPanelData(panelData);
    
    return pSprite;
}