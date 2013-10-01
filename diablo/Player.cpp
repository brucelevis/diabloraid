//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    hp            = new HitPoint(100); //base hp
    strength      = new Strength(5); //base damage
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

SwordDamage* Player::getSwordDamage(){
    return swordDamage;
}

PotionRecover* Player::getPotionRecover(){
    return potionRecover;
}

ShieldRefill* Player::getShieldRefill(){
    return shieldRefill;
}

//ダメージを受けたらhpを減らす。
void Player::damage(int v){
    hp->reduce(v);
}

//回復したらhpを増やす。
void Player::recover(int v){
    hp->increase(v);
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
    int totalDamage = strength->getValue();
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