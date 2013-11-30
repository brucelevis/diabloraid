//
//  EnemySkillMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/30.
//
//

#include "EnemySkillMaster.h"

EnemySkillMaster::EnemySkillMaster(int v){
    _records = Util::JsonParser::parse("master/enemy_skill.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    picojson::object &rec = records[idString->getCString()].get<picojson::object>();
    name = rec["name"].get<std::string>();
    id = rec["id"].get<double>();
    value = rec["value"].get<double>();
    imageId = rec["imageId"].get<double>();
}

EnemySkillMaster::~EnemySkillMaster(){
}

int EnemySkillMaster::getId(){
    return id;
}

EnemySkillMaster* EnemySkillMaster::getById(int v){
    EnemySkillMaster *enemy = new EnemySkillMaster(v);
    return enemy;
}

std::string EnemySkillMaster::getName(){
    return this->name;
}

int EnemySkillMaster::getValue(){
    return this->value;
}

int EnemySkillMaster::getImageId(){
    return this->imageId;
}