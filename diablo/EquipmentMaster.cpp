//
//  EquipmentMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/07.
//
//

#include "EquipmentMaster.h"

#include "cocos2d.h"
using namespace cocos2d;

EquipmentMaster::EquipmentMaster(int v){
    _records = Util::JsonParser::parse("master/equipment_master.json");
    picojson::object &records = _records.get<picojson::object>();
    
    CCString* idString = CCString::createWithFormat("%d",v);
    picojson::object &rec = records[idString->getCString()].get<picojson::object>();
    _name = rec["name"].get<std::string>();
    _id = rec["id"].get<double>();
    imageId    = rec["imageid"].get<double>();
    imageColor = rec["imagecolor"].get<double>();
    description = rec["description"].get<std::string>();
    _category  = rec["category"].get<double>();
    int _hp    = rec["hp"].get<double>();
    int _bd    = rec["basedamage"].get<double>();
    int _sd    = rec["sworddamage"].get<double>();
    int _pr    = rec["potionrecover"].get<double>();
    int _ss    = rec["shieldstatus"].get<double>();
    int _sr    = rec["shieldrefill"].get<double>();
    int _ca    = rec["coinaddition"].get<double>();
    int _str   = rec["strength"].get<double>();
    int _def   = rec["defense"].get<double>();
    int _dex   = rec["dexterity"].get<double>();
    int _vit   = rec["vitality"].get<double>();
    CCDictionary* dict  = CCDictionary::create();
    dict->setObject(CCInteger::create(_hp), "hp");
    dict->setObject(CCInteger::create(_bd), "baseDamage");
    dict->setObject(CCInteger::create(_sd), "swordDamage");
    dict->setObject(CCInteger::create(_pr), "potionRecover");
    dict->setObject(CCInteger::create(_ss), "shieldStatus");
    dict->setObject(CCInteger::create(_sr), "shieldRefill");
    dict->setObject(CCInteger::create(_ca), "coinAddition");
    dict->setObject(CCInteger::create(_str), "strength");
    dict->setObject(CCInteger::create(_def), "defense");
    dict->setObject(CCInteger::create(_dex), "dexterity");
    dict->setObject(CCInteger::create(_vit), "vitality");
    attributes = Attributes::createWithCCDictionary(dict);
}

EquipmentMaster::~EquipmentMaster(){
}

int EquipmentMaster::getId(){
    return _id;
}

EquipmentMaster* EquipmentMaster::getById(int v){
    EquipmentMaster *item = new EquipmentMaster(v);
    return item;
}

std::string EquipmentMaster::getName(){
    return this->_name;
}

int EquipmentMaster::getMaxHp(){
    return this->attributes->getMaxHp();
}

int EquipmentMaster::getShieldMaxHp(){
    return this->attributes->getShieldMaxHp();
}

int EquipmentMaster::getPotionRecover(){
    return this->attributes->getPotionRecover();
}

int EquipmentMaster::getShieldRefill(){
    return  this->attributes->getShieldRefill();
}

int EquipmentMaster::getSwordDamage(){
    return this->attributes->getSwordDamage();
}

int EquipmentMaster::getBaseDamage(){
    return this->attributes->getBaseDamage();
}

int EquipmentMaster::getCoinAddition(){
    return this->attributes->getCoinAddition();
}

int EquipmentMaster::getStrength(){
    return this->attributes->getStrength();
}

int EquipmentMaster::getDefense(){
    return this->attributes->getDefense();
}

int EquipmentMaster::getDexterity(){
    return this->attributes->getDexterity();
}

int EquipmentMaster::getVitality(){
    return this->attributes->getVitality();
}

int EquipmentMaster::getCategory(){
    return _category;
}