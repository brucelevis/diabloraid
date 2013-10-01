//
//  Attributes.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "Attributes.h"

Attributes::Attributes(){
    hp            = new HitPoint(100); //base hp
    baseDamage    = new BaseDamage(5); //base damage
    swordDamage   = new SwordDamage(20);
    potionRecover = new PotionRecover(3);
    shieldStatus  = new ShieldStatus(10);  //shieldStatus
    shieldRefill  = new ShieldRefill(2);
}

Attributes::~Attributes(){
}

int Attributes::getSwordDamage(){
    return this->swordDamage->getDamage();
}

int Attributes::getPotionRecover(){
    return this->potionRecover->getValue();
}

int Attributes::getShieldRefill(){
    return this->shieldRefill->getValue();
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
    return this->baseDamage->getValue();
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
