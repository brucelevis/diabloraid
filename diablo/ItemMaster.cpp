//
//  ItemMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/07.
//
//

#include "ItemMaster.h"

#include "cocos2d.h"
using namespace cocos2d;

ItemMaster::ItemMaster(int v){
    _records = Util::JsonParser::parse("master/item_master.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    picojson::object &rec = records[idString->getCString()].get<picojson::object>();
    _name = rec["name"].get<std::string>();
    description = rec["description"].get<std::string>();
    _id = rec["id"].get<double>();
    type = rec["type"].get<double>();
    value = rec["value"].get<double>();
}

ItemMaster::~ItemMaster(){
}

int ItemMaster::getId(){
    return _id;
}

int ItemMaster::getType(){
    return type;
}

int ItemMaster::getValue(){
    return value;
}

ItemMaster* ItemMaster::getById(int v){
    ItemMaster *item = new ItemMaster(v);
    return item;
}

std::string ItemMaster::getName(){
    return this->_name;
}

std::string ItemMaster::getDescription(){
    return this->description;
}