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
    hp->increaseMaxHp(vitality->getCalculatedHp(vitality->getCurrent()));
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

int Attributes::getCoinAddition(){
    return this->dexterity->getCurrent();
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

void Attributes::recoverAllHp(){
    hp->recoverAll();
}

//シールドのhpを回復する。
void Attributes::recoverShield(int v){
    shieldStatus->increase(v);
}

bool Attributes::isAlive(){
    return hp->getCurrentHp() > 0;
}

void Attributes::addStrength(int v){
    strength->add(v);
}

void Attributes::addDefense(int v){
    defense->add(v);
}

void Attributes::addDexterity(int v){
    dexterity->add(v);
}

void Attributes::addVitality(int v){
    vitality->add(v);
    hp->increaseMaxHp(vitality->getCalculatedHp(v)); //上昇させる。
}

Attributes* Attributes::getAttributesMock(){
    return new Attributes();
}
