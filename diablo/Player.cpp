//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    level         = new Level();
    attributes    = new Attributes();
    accumDamages  = CCArray::create();
    accumDamages->retain();
    events = (Events*) Events::create();
    events->retain();
}

int Player::getSwordDamage(){
    return attributes->getSwordDamage();
}

int Player::getPotionRecover(){
    return attributes->getPotionRecover();
}

int Player::getShieldRefill(){
    return attributes->getShieldRefill();
}

int Player::getCurrentHp(){
    return attributes->getCurrentHp();
}

int Player::getMaxHp(){
    return attributes->getMaxHp();
}

int Player::getShieldCurrentHp(){
    return attributes->getShieldCurrentHp();
}

int Player::getShieldMaxHp(){
    return attributes->getShieldMaxHp();
}

int Player::getCurrentLevel(){
    return this->level->getCurrentLevel();
}

int Player::getCurrentExp(){
    return this->level->getCurrentExp();
}

// ダメージを受けたらhpを減らす。
void Player::damage(int v){
    attributes->damage(v);
}
// シールドにダメージを与える。
void Player::damageToShield(int v){
    attributes->damageToShield(v);
}

//回復したらhpを増やす。
void Player::recover(int v){
    attributes->recover(v);
}


//シールドのhpを回復する。
void Player::recoverShield(int v){
    attributes->recoverShield(v);
}

bool Player::isAlive(){
    return attributes->isAlive();
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
    int totalDamage = attributes->getBaseDamage();
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
