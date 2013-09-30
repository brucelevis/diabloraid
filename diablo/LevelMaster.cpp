//
//  LevelMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#include "LevelMaster.h"

LevelMaster::LevelMaster(int v){
    _records = Util::JsonParser::parse("master/level.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    picojson::object &rec = records[idString->getCString()].get<picojson::object>();
    _level   = rec["level"].get<double>();
    _currentLevelExp = rec["current_level_exp"].get<double>();
    _requiredExp = rec["required_exp"].get<double>();
}

LevelMaster::~LevelMaster(){
}

LevelMaster* LevelMaster::getById(int v){
    LevelMaster *level = new LevelMaster(v);
    return level;
}

int LevelMaster::getLevel(int level, int exp){
    //現在のレベルのデータ
    LevelMaster *levelMaster = LevelMaster::getById(level);
    int addedExp = exp - levelMaster->_currentLevelExp;
    if (addedExp < levelMaster->_requiredExp){
        //必要経験値より下回っている時はレベルアップしない。
        return level;
    }
    
    return LevelMaster::getLevel(level+1, exp);
}

