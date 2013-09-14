//
//  EnemyFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#include "EnemyFactory.h"

Enemy* EnemyFactory::getEnemyPanel(){
    //将来的には、フロアの敵マップからenemyIdを取るようにする。
    int enemyId = rand() % 3 + 1;
    EnemyMaster* enemy = EnemyMaster::getById(enemyId);
    return Enemy::createWithSpriteFrameName(enemy->getName().c_str(), enemy->getHp(), enemy->getAttack(), enemy->getDef());
}