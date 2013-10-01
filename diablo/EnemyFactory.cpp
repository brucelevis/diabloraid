//
//  EnemyFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#include "EnemyFactory.h"

Enemy* EnemyFactory::getEnemyPanel(Floor* floor){
    int currentFloor = floor->getFloor();
    FloorEnemyMapMaster* master = FloorEnemyMapMaster::getById(currentFloor);
    CCArray* enemies = master->getEnemies();
    CCDictionary* enemyMap;
    CCObject* targetObject;
    
    //将来的には、フロアの敵マップからenemyIdを取るようにする。
    int enemyId;
    int probability = rand() % 100 + 1;
    CCARRAY_FOREACH(enemies, targetObject){
        enemyMap = (CCDictionary*) targetObject;
        CCInteger* prob =(CCInteger*) enemyMap->objectForKey("probability");
        if(prob->getValue() >= probability){
            enemyId = ((CCInteger*) enemyMap->objectForKey("enemyId"))->getValue();
            break;
        }
        probability -= prob->getValue();
    }
    
    EnemyMaster* enemy = EnemyMaster::getById(enemyId);
    return Enemy::createWithSpriteFrameName(enemy->getName().c_str(), enemy);
}