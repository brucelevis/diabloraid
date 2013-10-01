//
//  Attributes.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "Attributes.h"

Attributes::Attributes(){
    hp            = new HitPoint(50); //base hp
    vitality      = new Vitality(5);
    hp->increaseMaxHp(vitality->getCalculatedHp());
    hp->recoverAll();
    
    swordDamage   = new SwordDamage(20);
    potionRecover = new PotionRecover(3);
    shieldStatus  = new ShieldStatus(10);  //shieldStatus
    strength      = new AttributeBase(5);
    defense       = new AttributeBase(2);
    dexterity     = new AttributeBase(5);
}

Attributes::~Attributes(){
}

int Attributes::getStrength(){
    return strength->getCurrent();
}

int Attributes::getDefense(){
    return defense->getCurrent();
}

int Attributes::getVitality(){
    return vitality->getCurrent();
}

int Attributes::getDexterity(){
    return dexterity->getCurrent();
}


int Attributes::getSwordDamage(){
    return this->swordDamage->getDamage();
}

int Attributes::getPotionRecover(){
    return this->potionRecover->getValue();
}

int Attributes::getShieldRefill(){
    return this->defense->getCurrent();
}

int Attributes::getCurrentHp(){
    return this->hp->getCurrentHp();
}

int Attributes::getMaxHp(){
    return this->hp->getMaxHp();
}

int Attributes::getShieldCurrentHp(){
    return this->shieldStatus->getCurrent();
}

int Attributes::getShieldMaxHp(){
    return this->shieldStatus->getMax();
}

int Attributes::getBaseDamage(){
    return this->strength->getCurrent();
}

// ダメージを受けたらhpを減らす。
void Attributes::damage(int v){
    hp->reduce(v);
}
// シールドにダメージを与える。
void Attributes::damageToShield(int v){
    this->shieldStatus->damage(v);
}

//回復したらhpを増やす。
void Attributes::recover(int v){
    hp->increase(v);
}


//シールドのhpを回復する。
void Attributes::recoverShield(int v){
    shieldStatus->increase(v);
}

bool Attributes::isAlive(){
    return hp->getCurrentHp() > 0;
}

Attributes* Attributes::getAttributesMock(){
    return new Attributes();
}