//
//  Belongings.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#include "Belongings.h"

Belongings::Belongings(){
    _null  = new UserItem();
    
    sword  = _null;
    shield = _null;
    armor  = _null;
}

bool Belongings::isEquipped(UserItem* equipment){
    return (sword == equipment)  ? true
    : (shield == equipment) ? true
    : (armor  == equipment) ? true
    : false;
}

UserItem* Belongings::get(int category){
    switch(category){
        case 1:
            return sword;
            break;
        case 2:
            return shield;
            break;
        case 3:
            return armor;
            break;
        default:
            return _null;
            break;
    }
}

int Belongings::getMaxHp(){
    return sword->getMaxHp() + shield->getMaxHp() + armor->getMaxHp();
}

int Belongings::getShieldMaxHp(){
    return sword->getShieldMaxHp() + shield->getShieldMaxHp() + armor->getShieldMaxHp();
}

int Belongings::getPotionRecover(){
    return sword->getPotionRecover() + shield->getPotionRecover() + armor->getPotionRecover();
}

int Belongings::getShieldRefill(){
    return sword->getShieldRefill() + shield->getShieldRefill() + armor->getShieldRefill();
}

int Belongings::getSwordDamage(){
    return sword->getSwordDamage() + shield->getSwordDamage() + armor->getSwordDamage();
}

int Belongings::getBaseDamage(){
    return sword->getBaseDamage() + shield->getBaseDamage() + armor->getBaseDamage();
}

int Belongings::getCoinAddition(){
    return sword->getCoinAddition() + shield->getCoinAddition() + armor->getCoinAddition();
}

int Belongings::getStrength(){
    return sword->getStrength() + shield->getStrength() + armor->getStrength();
}
int Belongings::getDefense(){
    return sword->getDefense() + shield->getDefense() + armor->getDefense();
}
int Belongings::getDexterity(){
    return sword->getDexterity() + shield->getDexterity() + armor->getDexterity();
}
int Belongings::getVitality(){
    return sword->getVitality() + shield->getVitality() + armor->getVitality();
}

Belongings::~Belongings(){
}

void Belongings::set(UserItem* equipment){
    CCLOG("Belongings::set : %d", equipment->getCategory());
    this->unset(equipment);
    switch (equipment->getCategory()) {
        case 1:
            CCLOG("set sword");
            this->sword = equipment;
            break;
        case 2:
            CCLOG("set shield");
            this->shield = equipment;
            break;
        case 3:
            CCLOG("set armor");
            this->armor = equipment;
            break;
        default:
            break;
    }
}

void Belongings::unset(UserItem* equipment){
       switch (equipment->getCategory()) {
        case 1:
            this->sword->setEquipped(false);
            this->sword = _null;
            break;
        case 2:
            this->shield->setEquipped(false);
            this->shield = _null;
            break;
        case 3:
            this->armor->setEquipped(false);
            this->armor = _null;
            break;
        default:
            break;
       }
}
