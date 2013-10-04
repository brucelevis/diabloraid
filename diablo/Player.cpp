//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    level         = new Level();
    budget        = new Budget();
    levelUpCount  = 0;
    attributes    = Attributes::createWithDefault();
    accumDamages  = CCArray::create();
    accumDamages->retain();
}

Attributes* Player::getAttributes(){
    return attributes;
}

int Player::getBaseDamage(){
    return attributes->getBaseDamage();
}

int Player::getSwordDamage(){
    return attributes->getSwordDamage();
}

int Player::getPotionRecover(){
    return attributes->getPotionRecover();
}

int Player::getCoinAddition(){
    return attributes->getCoinAddition();
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

int Player::getStrength(){
    return this->attributes->getStrength();
}

int Player::getDefense(){
    return this->attributes->getDefense();
}

int Player::getDexterity(){
    return this->attributes->getDexterity();
}

int Player::getVitality(){
    return this->attributes->getVitality();
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

void Player::recoverAllHp(){
    attributes->recoverAllHp();
}


//シールドのhpを回復する。
void Player::recoverShield(int v){
    attributes->recoverShield(v);
}

bool Player::isAlive(){
    return attributes->isAlive();
}

void Player::addCoin(){
    this->budget->add(this->attributes->getCoinAddition());
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

int Player::getBudget(){
    return this->budget->getCurrent();
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

void Player::addExp(int addedExp){
    CCLOG("Player::addExp: %d", addedExp);
    levelUpCount += this->level->addExp(addedExp);
    CCLOG("Player::after addExp: levelUpCount%d", levelUpCount);
}

int Player::getLevelUpCount(){
    CCLOG("Player::getLevelUpCount: %d", levelUpCount);
    return levelUpCount;
}

void Player::resetLevelUpCount(){
    levelUpCount = 0;
}

Player* Player::getPlayerMock(){
    return new Player();
}

void Player::setAttributes(Attributes* attributes){
    this->attributes = attributes;
}