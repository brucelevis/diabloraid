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
    std::string panelName = ((CCString*) convertToPanelName(panelType))->getCString();
    
    PanelSprite* pSprite;
    int type = panelType; //とりま。
    int typeInstanceId; //とりま。
    if(panelName == "enemy"){
        EnemyData* enemy = EnemyFactory::createEnemy(floor);
        typeInstanceId = enemy->getId();
        pSprite = Enemy::createWithEnemyMaster(enemy->master);
    } else if(panelName == "potion"){
        typeInstanceId = 0;
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "sword"){
        typeInstanceId = 0;
        pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "coin"){
        typeInstanceId = 0;
        pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "shield"){
        typeInstanceId = 0;
        pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "kaidan"){
        typeInstanceId = 0;
        pSprite = Stair::createWithSpriteFrameName(panelName.c_str());
    } else {
        type = -1;
        typeInstanceId = 0;
        pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
    }
    PanelData* panelData = PanelData::create(type, typeInstanceId);
    ModelManager* modelManager = ModelManager::getInstance();
    PanelDataManager* panelDataManager =(PanelDataManager*) modelManager->getModel("PanelData");
    panelDataManager->add(panelData);
    
    CCLOG("panelData: id:%d, type: %d, typeInstanceId: %d", panelData->getId(), panelData->getType(), panelData->getTypeInstanceId());
    //そもそもpanelDataから生成するようにしたいところ
    pSprite->setPanelData(panelData);
    
    return pSprite;
}

PanelData* PanelSpriteFactory::createPanelDataWithFloor(Floor *floor){
    int panelType = floor->createPanel();
    std::string panelName = ((CCString*) convertToPanelName(panelType))->getCString();
    ModelManager* modelManager = ModelManager::getInstance();
    
    int type = panelType; //とりま。
    int typeInstanceId = 0; //とりま。
    if(panelName == "enemy"){
        EnemyData* enemy = EnemyFactory::createEnemy(floor);
        EnemyDataManager* enemyDataManager = (EnemyDataManager*) modelManager->getModel("EnemyData");
        enemyDataManager->add(enemy);
        typeInstanceId = enemy->getId();
    }
    
    PanelData* panelData = PanelData::create(type, typeInstanceId);
    PanelDataManager* panelDataManager =(PanelDataManager*) modelManager->getModel("PanelData");
    panelDataManager->add(panelData);
    return panelData;
}

PanelSprite* PanelSpriteFactory::createByPanelData(PanelData* panelData){
    int type = panelData->getType();
    std::string panelName = ((CCString*) convertToPanelName(type))->getCString();
    PanelSprite *pSprite;
    switch (type) {
        case -1:
            pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
            break;
        case 0:
            pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
            break;
        case 1:
            {
                ModelManager* modelManager = ModelManager::getInstance();
                EnemyDataManager* enemyDataManager = (EnemyDataManager*) modelManager->getModel("EnemyData");
                EnemyData* enemyData = enemyDataManager->getByPrimaryKey(panelData->getTypeInstanceId());
                pSprite = Enemy::createWithEnemyData(enemyData);
            }
            break;
        case 2:
            pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
            break;
        case 3:
            pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
            break;
        case 4:
            pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
            break;
        case 5:
            pSprite = Stair::createWithSpriteFrameName(panelName.c_str());
            break;
        default:
            break;
    }
    pSprite->setPanelData(panelData);
    return pSprite;
}

CCString* PanelSpriteFactory::convertToPanelName(int panelType){
    CCDictionary* _panelNameMap = CCDictionary::create();

    _panelNameMap->setObject((CCObject*) new CCString("coin"), 0);
    _panelNameMap->setObject((CCObject*) new CCString("enemy"), 1);
    _panelNameMap->setObject((CCObject*) new CCString("shield"), 2);
    _panelNameMap->setObject((CCObject*) new CCString("sword"), 3);
    _panelNameMap->setObject((CCObject*) new CCString("potion"), 4);
    _panelNameMap->setObject((CCObject*) new CCString("kaidan"), 5);
    _panelNameMap->setObject((CCObject*) new CCString(""), -1);
    return (CCString*) _panelNameMap->objectForKey(panelType);
}

int PanelSpriteFactory::convertToPanelType(std::string panelName){
    CCDictionary* _panelNameMap = CCDictionary::create();

    _panelNameMap->setObject((CCObject*) new CCInteger(0), "coin");
    _panelNameMap->setObject((CCObject*) new CCInteger(1), "enemy");
    _panelNameMap->setObject((CCObject*) new CCInteger(2), "shield");
    _panelNameMap->setObject((CCObject*) new CCInteger(3), "sword");
    _panelNameMap->setObject((CCObject*) new CCInteger(4), "potion");
    _panelNameMap->setObject((CCObject*) new CCInteger(5), "kaidan");
    _panelNameMap->setObject((CCObject*) new CCInteger(-1), "");
    return ((CCInteger*) _panelNameMap->objectForKey(panelName))->getValue();
}

