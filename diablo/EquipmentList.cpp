//
//  EquipmentList.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#include "EquipmentList.h"

EquipmentList* EquipmentList::getAll(){
    EquipmentList* array = (EquipmentList*) EquipmentList::create();
    picojson::value _records = Util::JsonParser::parse("master/equipment_list.json");
    array->_equipped =(EquipmentList*) EquipmentList::create();
    array->_equipped->retain();
    
    picojson::array &records = _records.get<picojson::array>();
    picojson::array::iterator it;
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        Equipment* equipment = new Equipment(record);
        array->addObject((CCObject*) equipment);
    }
    array->reload();
    return array;
}



void EquipmentList::reload(){
    CCObject* targetObject;
    Equipment* equipment;
    
    _equipped->removeAllObjects();
    CCARRAY_FOREACH(this, targetObject){
        equipment = (Equipment*) targetObject;
        if(equipment->isEquipped()){
            _equipped->addObject((CCObject*) equipment);
        }
    }
}


int EquipmentList::getMaxHp(){
    CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getMaxHp();
    }
    return total;
}

int EquipmentList::getShieldMaxHp(){
    CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getShieldMaxHp();
    }
    return total;
}

int EquipmentList::getPotionRecover(){
    CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getPotionRecover();
    }
    return total;
}

int EquipmentList::getShieldRefill(){
    CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getShieldRefill();
    }
    return total;
}

int EquipmentList::getSwordDamage(){
    CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getSwordDamage();
    }
    return total;
}

int EquipmentList::getBaseDamage(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getBaseDamage();
    }
    return total;
}

int EquipmentList::getCoinAddition(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getCoinAddition();
    }
    return total;
}

int EquipmentList::getStrength(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getStrength();
    }
    return total;
}
int EquipmentList::getDefense(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getDefense();
    }
    return total;
}
int EquipmentList::getDexterity(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getDexterity();
    }
    return total;
}

int EquipmentList::getVitality(){
       CCObject* targetObject;
    Equipment* equipment;
    
    int total = 0;
    if(!_equipped->count()){
        return 0;
    }
    CCARRAY_FOREACH(_equipped, targetObject){
        equipment = (Equipment*) targetObject;
        total += equipment->getVitality();
    }
    return total;
}
