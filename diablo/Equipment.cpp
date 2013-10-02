//
//  Equipment.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#include "Equipment.h"

Equipment::Equipment(picojson::object rec){
    imageId = rec["imageid"].get<double>();
    name    = rec["name"].get<std::string>();
}

Equipment::~Equipment(){
}

std::string Equipment::getName(){
    return name;
}

CCArray* Equipment::getAll(){
    CCArray* array = CCArray::create();
    picojson::value _records = Util::JsonParser::parse("master/equipment_list.json");
    
    picojson::array &records = _records.get<picojson::array>();
    picojson::array::iterator it;
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        Equipment* equipment = new Equipment(record);
        array->addObject((CCObject*) equipment);
    }
    return array;
}