//
//  UserItems.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/11.
//
//

#include "UserItems.h"
UserItems* UserItems::create()
{
    UserItems* pArray = new UserItems();
    
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

void UserItems::setBelongings(){
    UserItem* userItem;
    CCObject* targetObject;
    CCARRAY_FOREACH(this, targetObject){
        userItem = (UserItem*) targetObject;
        if(userItem->isEquipped()){
            _equipped->set(userItem);
        }
    }
}

Belongings* UserItems::getBelongings(){
    return _equipped;
}

UserItems* UserItems::getAll(){
    UserItems* array = UserItems::create();
    picojson::value _records = Util::JsonParser::parse("master/user_item.json");
    
    picojson::array &records = _records.get<picojson::array>();
    picojson::array::iterator it;
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        map<string, string> entity;
        entity["id"]   = Util::Util::intToString(record["id"].get<double>());
        entity["type"] = Util::Util::intToString(record["type"].get<double>());
        entity["itemId"] = Util::Util::intToString(record["itemId"].get<double>());
        entity["isEquip"] = Util::Util::intToString(record["isEquip"].get<double>());
        UserItem* userItem   = new UserItem(entity);
        userItem->setMaster(UserItem::createMaster(userItem));
        array->addObject((CCObject*) userItem);
    }
    return array;
}

UserItem* UserItems::getById(int id){
    CCObject* targetObject;
    UserItem* userItem;
    CCARRAY_FOREACH(this, targetObject){
        userItem = (UserItem*) targetObject;
        if(userItem->getId() == id){
            return userItem;
        }
    }
    return NULL;
}

int UserItems::getMaxHp(){
    return _equipped->getMaxHp();
}

int UserItems::getShieldMaxHp(){
    return _equipped->getShieldMaxHp();
}

int UserItems::getPotionRecover(){
    return _equipped->getPotionRecover();
}

int UserItems::getShieldRefill(){
    return _equipped->getShieldRefill();
}

int UserItems::getSwordDamage(){
    return _equipped->getSwordDamage();
}

int UserItems::getBaseDamage(){
    return _equipped->getBaseDamage();
}

int UserItems::getCoinAddition(){
    return _equipped->getCoinAddition();
}

int UserItems::getStrength(){
    return _equipped->getStrength();
}
int UserItems::getDefense(){
    return _equipped->getDefense();
}
int UserItems::getDexterity(){
    return _equipped->getDexterity();
}

int UserItems::getVitality(){
    return _equipped->getVitality();
}

UserItems::UserItems(){
    _equipped = new Belongings();
}

UserItems::~UserItems(){
}

//アイテムを追加する。
void UserItems::add(int type, int itemId){
    map<string, string> entity;
    entity["type"] = Util::Util::intToString(type);
    entity["itemId"] = Util::Util::intToString(itemId);
    entity["isEquip"] = Util::Util::intToString(0);
    UserItem* userItem   = new UserItem(entity);
    userItem->setMaster(UserItem::createMaster(userItem));
    this->addObject((CCObject*) userItem);
}

//アイテムを削除する。
void UserItems::remove(int id){
    UserItem* removedItem = this->getById(id);
    this->removeObject((CCObject*) removedItem);
    delete removedItem;
}