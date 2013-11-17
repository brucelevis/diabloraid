//
//  UserItem.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/07.
//
//

#include "UserItem.h"


int UserItem::seqId = 1;

int UserItem::getSeqId(){
    return seqId++;
}


UserItem::UserItem(map<string, string> entity){
    id        = UserItem::getSeqId();
    type      = atoi(entity["type"].c_str());
    itemId    = atoi(entity["itemId"].c_str());
    isEquip   = (atoi(entity["isEquip"].c_str()) == 1) ? true : false;
}

UserItem::UserItem(){
    id      = 0;
    type    = -1;
    itemId  = 0;
    isEquip = false;
}


UserItem::~UserItem(){
}

HavingMasterInterface* UserItem::createMaster(UserItem *userItem){
    ModelManager* modelManager = ModelManager::getInstance();
    switch(userItem->getType()){
        // 装備の場合
        case EQUIPMENT:
        {
            
            ModelInstanceManager* modelInstanceManager = modelManager->getModel("EquipmentMaster");
            return (EquipmentMaster*) modelInstanceManager->getByPrimaryKey(userItem->getItemId());
        }
        // 消耗品の場合
        case USABLE:
        {
            ModelInstanceManager* modelInstanceManager = modelManager->getModel("ItemMaster");
            return (ItemMaster*) modelInstanceManager->getByPrimaryKey(userItem->getItemId());
        }
        default:
            break;
    }
}

bool UserItem::isEquipped(){
    if (!this->isEquipment()){
        return false;
    }
    return this->isEquip;
}

bool UserItem::isEquipment(){
   switch(this->getType()){
       case EQUIPMENT:
        return true;
       case USABLE:
        return false;
       default:
        return false;
   }
}

void UserItem::setMaster(HavingMasterInterface *master){
    this->master = master;
}

int UserItem::getId(){
    return id;
}

int UserItem::getType(){
    return type;
}

int UserItem::getItemId(){
    return itemId;
}

std::string UserItem::getName(){
    return master->getName();
}

int UserItem::getMaxHp(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getMaxHp();
}

int UserItem::getShieldMaxHp(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getShieldMaxHp();
}

int UserItem::getPotionRecover(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getPotionRecover();
}

int UserItem::getShieldRefill(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getShieldRefill();
}

int UserItem::getSwordDamage(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getSwordDamage();
}

int UserItem::getBaseDamage(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getBaseDamage();
}

int UserItem::getCoinAddition(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getCoinAddition();
}

int UserItem::getStrength(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getStrength();
}

int UserItem::getDefense(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getDefense();
}

int UserItem::getDexterity(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getDexterity();
}

int UserItem::getVitality(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getVitality();
}

int UserItem::getCategory(){
    if(!this->isEquipment()){
        return 0;
    }
    return ((EquipmentMaster*)this->master)->getCategory();
}

void UserItem::setEquipped(bool _isEquipped){
    if(!this->isEquipment()){
        return;
    }
    this->isEquip = _isEquipped;
}

UserItem* UserItem::getMock(int type){
    picojson::object record;
    switch(type){
        case EQUIPMENT:
        {
            picojson::value equipment = Util::JsonParser::parse("master/mock/equipment.json");
            record = equipment.get<picojson::object>();
        }
            break;
        case USABLE:
        {
            picojson::value usable = Util::JsonParser::parse("master/mock/usable.json");
            record = usable.get<picojson::object>();
            
        }
            break;
        default:
            break;
    }
    map<string, string> entity;
    entity["id"]   = Util::Util::intToString(record["id"].get<double>());
    entity["type"] = Util::Util::intToString(record["type"].get<double>());
    entity["itemId"] = Util::Util::intToString(record["itemId"].get<double>());
    entity["isEquip"] = Util::Util::intToString(record["isEquip"].get<double>());
    UserItem* userItem   = new UserItem(entity);
    userItem->setMaster(UserItem::createMaster(userItem));
    return userItem;
}