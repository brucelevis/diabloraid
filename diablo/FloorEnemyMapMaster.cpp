//
//  FloorEnemyMapMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "FloorEnemyMapMaster.h"

FloorEnemyMapMaster::FloorEnemyMapMaster(int v){
    CCLOG("FloorId:%d", v);
    _records = Util::JsonParser::parse("master/floor_enemy_map.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    _enemies = CCArray::create();
    _enemies->retain();
    picojson::array &rec = records[idString->getCString()].get<picojson::array>();
    picojson::array::iterator it;
    for(it = rec.begin(); it != rec.end(); it++){
        picojson::object& enemyRecord = it->get<picojson::object>();
        int floor_id    = enemyRecord["floor_id"].get<double>();
        int probability = enemyRecord["probability"].get<double>();
        int maxNum      = enemyRecord["max_num"].get<double>();
        int enemyId      = enemyRecord["enemy_id"].get<double>();
        //CCDictionaryクラスを作ってCCArrayに突っ込む
        CCDictionary* enemy = CCDictionary::create();
        enemy->setObject(CCInteger::create(floor_id), "floorId");
        enemy->setObject(CCInteger::create(probability), "probability");
        enemy->setObject(CCInteger::create(maxNum), "maxNum");
        enemy->setObject(CCInteger::create(enemyId), "enemyId");
        _enemies->addObject(enemy);
    }
}

FloorEnemyMapMaster* FloorEnemyMapMaster::getById(int v){
    FloorEnemyMapMaster *enemyMapMaster = new FloorEnemyMapMaster(v);
    return enemyMapMaster;
}

CCArray* FloorEnemyMapMaster::getEnemies(){
    return _enemies;
}

FloorEnemyMapMaster::~FloorEnemyMapMaster(){
}