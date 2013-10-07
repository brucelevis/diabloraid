//
//  EquipmentList.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#include "EquipmentList.h"
EquipmentList* EquipmentList::create()
{
    EquipmentList* pArray = new EquipmentList();
    
    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

EquipmentList* EquipmentList::getAll(){
    EquipmentList* array =(EquipmentList*) EquipmentList::create();
    picojson::value _records = Util::JsonParser::parse("master/equipment_list.json");
    
    picojson::array &records = _records.get<picojson::array>();
    picojson::array::iterator it;
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        Equipment* equipment = new Equipment(record);
        CCLOG("getAll category : %d", equipment->getCategory());
        array->addObject((CCObject*) equipment);
    }
    return array;
}

void EquipmentList::reload(){
    Equipment* equipment;
    CCObject* targetObject;
    CCARRAY_FOREACH(this, targetObject){
        equipment = (Equipment*) targetObject;
        if(_equipped->isEquipped(equipment)){
            equipment->setEquipped(true);
        } else {
            equipment->setEquipped(false);
        }
    }
}

void EquipmentList::setBelongings(){
    Equipment* equipment;
    CCObject* targetObject;
    CCARRAY_FOREACH(this, targetObject){
        equipment = (Equipment*) targetObject;
        if(equipment->isEquipped()){
            _equipped->set(equipment);
        }
    }
}

void EquipmentList::add(Equipment* equipment){
    CCLOG("isEquip:%d", equipment->isEquipped());
    this->addObject((CCObject*) equipment);
}

Belongings* EquipmentList::getBelongings(){
    return _equipped;
}


int EquipmentList::getMaxHp(){
    return _equipped->getMaxHp();
}

int EquipmentList::getShieldMaxHp(){
    return _equipped->getShieldMaxHp();
}

int EquipmentList::getPotionRecover(){
    return _equipped->getPotionRecover();
}

int EquipmentList::getShieldRefill(){
    return _equipped->getShieldRefill();
}

int EquipmentList::getSwordDamage(){
    return _equipped->getSwordDamage();
}

int EquipmentList::getBaseDamage(){
    return _equipped->getBaseDamage();
}

int EquipmentList::getCoinAddition(){
    return _equipped->getCoinAddition();
}

int EquipmentList::getStrength(){
    return _equipped->getStrength();
}
int EquipmentList::getDefense(){
    return _equipped->getDefense();
}
int EquipmentList::getDexterity(){
    return _equipped->getDexterity();
}

int EquipmentList::getVitality(){
    return _equipped->getVitality();
}

EquipmentList::EquipmentList(){
    _equipped = new Belongings();
}

EquipmentList::~EquipmentList(){
}