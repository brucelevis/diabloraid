//
//  EnemyDataManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/27.
//
//

#include "EnemyDataManager.h"

// fileから読むなり、なんなりするとしてもこのクラスで行う。
EnemyDataManager::EnemyDataManager(){
    CCLOG("EnemyDataManager constructor");
    _modelMap = new map<string, EnemyData*>();
    name = "EnemyData";
}

EnemyDataManager::~EnemyDataManager(){
}

void EnemyDataManager::add(EnemyData* enemyData){
    std::string key = Util::Util::intToString(enemyData->getId());
    (*_modelMap)[key] = enemyData;
}

void EnemyDataManager::remove(EnemyData* enemyData){
    std::string key = Util::Util::intToString(enemyData->getId());
    (*_modelMap)[key] = NULL;
}

EnemyData* EnemyDataManager::getByPrimaryKey(int id){
    std::string key = Util::Util::intToString(id);
    return (*_modelMap)[key];
}

std::string EnemyDataManager::getModelName(){
    return name;
}