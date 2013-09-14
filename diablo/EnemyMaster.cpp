//
//  EnemyMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#include "EnemyMaster.h"
#include "Util.h"
#include "cocos2d.h"
using namespace cocos2d;

EnemyMaster::EnemyMaster(int v){
    _records = Util::JsonParser::parse("master/enemy.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    picojson::object &rec = records[idString->getCString()].get<picojson::object>();
    _name = rec["name"].get<std::string>();
    _hp = rec["hp"].get<double>();
    _id = rec["id"].get<double>();
    _attack = rec["attack"].get<double>();
    _def = rec["def"].get<double>();
}

EnemyMaster::~EnemyMaster(){
}

EnemyMaster* EnemyMaster::getById(int v){
    EnemyMaster *enemy = new EnemyMaster(v);
    return enemy;
}

int EnemyMaster::getDef(){
    return _def;
}

int EnemyMaster::getAttack(){
    return _attack;
}

int EnemyMaster::getHp(){
    return _hp;
}

std::string EnemyMaster::getName(){
    return this->_name;
}

