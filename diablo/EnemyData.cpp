//
//  EnemyData.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#include "EnemyData.h"

int EnemyData::seqId = 1;

int EnemyData::getSeqId(){
    return seqId++;
}

EnemyData* EnemyData::create(EnemyMaster* enemy){
    map<string, string> entity;
    entity["enemyId"]   = Util::Util::intToString(enemy->getId());
    entity["currentHp"] = Util::Util::intToString(enemy->getHp());
    EnemyData* enemyData = new EnemyData(entity);
    enemyData->master = enemy;
    return enemyData;
}

EnemyData::EnemyData(map<string, string> entity){
    id        = EnemyData::getSeqId();
    enemyId   = atoi(entity["enemyId"].c_str());
    currentHp = atoi(entity["currentHp"].c_str());
}

int EnemyData::getId(){
    return id;
}

int EnemyData::getEnemyId(){
    return enemyId;
}

int EnemyData::getCurrentHp(){
    return currentHp;
}
