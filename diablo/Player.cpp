//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    hp            = new HitPoint(100); //base hp
    baseDamage    = new BaseDamage(5); //base damage
    swordDamage   = new SwordDamage(20);
    potionRecover = new PotionRecover(3);
    shieldStatus  = new ShieldStatus(10);  //shieldStatus
    shieldRefill  = new ShieldRefill(2);
    level         = new Level();
    accumDamages  = CCArray::create();
    accumDamages->retain();
    events = (Events*) Events::create();
    events->retain();
}

int Player::getSwordDamage(){
    return swordDamage->getDamage();
}

int Player::getPotionRecover(){
    return potionRecover->getValue();
}

int Player::getShieldRefill(){
    return shieldRefill->getValue();
}

// ダメージを受けたらhpを減らす。
void Player::damage(int v){
    hp->reduce(v);
}
// シールドにダメージを与える。
void Player::damageToShield(int v){
    this->shieldStatus->damage(v);
}

//回復したらhpを増やす。
void Player::recover(int v){
    hp->increase(v);
}


//シールドのhpを回復する。
void Player::recoverShield(int v){
    shieldStatus->increase(v);
}

bool Player::isAlive(){
    return hp->getCurrentHp() > 0;
}

void Player::pushDamage(int v){
    accumDamages->addObject(CCInteger::create(v));
}

void Player::popDamage(){
    accumDamages->removeObject(accumDamages->lastObject());
}

void Player::resetDamage(){
    accumDamages->removeAllObjects();
}

int Player::getTotalDamage(){
    CCInteger* damage      = NULL;
    CCObject* targetObject = NULL;
    int totalDamage = baseDamage->getValue();
    CCARRAY_FOREACH(accumDamages, targetObject){
        damage = (CCInteger*) targetObject;
        totalDamage += damage->getValue();
    }
    return totalDamage;
}

void Player::pushLevelUpEvent(){
    events->addObject((CCObject*) EventFactory::create(1));
}

void Player::addExp(int addedExp){
    int levelUpCount = this->level->addExp(addedExp);
    int i;
    CCLOG("levelUpCount%d",levelUpCount);
    for(i = 0; i < levelUpCount; i++){
        CCLOG("levelup");
        this->pushLevelUpEvent();
    }
}

Events* Player::getEvent(){
    return this->events;
}

int Player::getCurrentHp(){
    return this->hp->getCurrentHp();
}

int Player::getMaxHp(){
    return this->hp->getMaxHp();
}

int Player::getShieldCurrentHp(){
    return this->shieldStatus->getCurrent();
}

int Player::getShieldMaxHp(){
    return this->shieldStatus->getMax();
}

int Player::getCurrentLevel(){
    return this->level->getCurrentLevel();
}

int Player::getCurrentExp(){
    return this->level->getCurrentExp();
}
