//
//  Equipment.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#include "Equipment.h"

Equipment::Equipment(picojson::object rec){
    imageId    = rec["imageid"].get<double>();
    name       = rec["name"].get<std::string>();
    id         = rec["id"].get<double>();
    imageColor = rec["imagecolor"].get<double>();
    description = rec["description"].get<std::string>();
    isEquip    = (rec["isequip"].get<double>() == 1) ? true : false;
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

int Equipment::getMaxHp(){
    return this->attributes->getMaxHp();
}

int Equipment::getShieldMaxHp(){
    return this->attributes->getShieldMaxHp();
}

int Equipment::getPotionRecover(){
    return this->attributes->getPotionRecover();
}

int Equipment::getShieldRefill(){
    return  this->attributes->getShieldRefill();
}

int Equipment::getSwordDamage(){
    return this->attributes->getSwordDamage();
}

int Equipment::getBaseDamage(){
    return this->attributes->getBaseDamage();
}

int Equipment::getCoinAddition(){
    return this->attributes->getCoinAddition();
}

int Equipment::getStrength(){
    return this->attributes->getStrength();
}

int Equipment::getDefense(){
    return this->attributes->getDefense();
}

int Equipment::getDexterity(){
    return this->attributes->getDexterity();
}

int Equipment::getVitality(){
    return this->attributes->getVitality();
}

void Equipment::setEquipped(bool _isEquipped){
    this->isEquip = _isEquipped;
}

bool Equipment::isEquipped(){
    return this->isEquip;
}

Equipment* Equipment::getMock(){
    picojson::value _mock = Util::JsonParser::parse("master/mock/equipment.json");
    return new Equipment(_mock.get<picojson::object>());
}

