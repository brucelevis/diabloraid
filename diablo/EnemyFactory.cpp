//
//  EnemyFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#include "EnemyFactory.h"

EnemyMaster* EnemyFactory::createEnemy(Floor* floor){
    int currentFloor = floor->getFloor();
    FloorEnemyMapMaster* master = FloorEnemyMapMaster::getById(currentFloor);
    CCArray* enemies = master->getEnemies();
    CCDictionary* enemyMap;
    CCObject* targetObject;
    
    //将来的には、フロアの敵マップからenemyIdを取るようにする。
    int enemyId;
    int maxExistsNum;
    int probability = rand() % 100 + 1;
    CCARRAY_FOREACH(enemies, targetObject){
        enemyMap = (CCDictionary*) targetObject;
        CCInteger* prob =(CCInteger*) enemyMap->objectForKey("probability");
        if(prob->getValue() >= probability){
            enemyId      = ((CCInteger*) enemyMap->objectForKey("enemyId"))->getValue();
            maxExistsNum = ((CCInteger*) enemyMap->objectForKey("maxNum"))->getValue();
            break;
        }
        probability -= prob->getValue();
    }
    
    EnemyMaster* enemy = EnemyMaster::getById(enemyId);
    enemy->setMaxExistsNum(maxExistsNum);
    EnemyData* enemyData = EnemyData::create(enemy);
    CCLOG("id:%d, enemyId:%d, currentHp:%d", enemyData->id, enemyData->enemyId, enemyData->currentHp);
    return enemy;
}