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
    userItem      = UserItems::getAll();
    userItem->setBelongings();
    userItem->retain();
    attributes    = Attributes::createWithDefault();
    accumDamages  = CCArray::create();
    accumDamages->retain();
    playerLog     = CCArray::create();
    playerLog->retain();
}

Attributes* Player::getAttributes(){
    return attributes;
}

UserItems* Player::getUserItem(){
    return userItem;
}

Belongings* Player::getBelongings(){
    return userItem->getBelongings();
}

int Player::getBaseDamage(){
    return attributes->getBaseDamage() + this->userItem->getBaseDamage();
}

int Player::getSwordDamage(){
    return attributes->getSwordDamage() + this->userItem->getSwordDamage();
}

int Player::getPotionRecover(){
    return attributes->getPotionRecover() + this->userItem->getPotionRecover();
}

int Player::getCoinAddition(){
    return attributes->getCoinAddition() + this->userItem->getCoinAddition();
}

int Player::getShieldRefill(){
    return attributes->getShieldRefill() + this->userItem->getShieldRefill();
}

int Player::getCurrentHp(){
    return attributes->getCurrentHp();
}

int Player::getMaxHp(){
    return attributes->getMaxHp() + this->userItem->getMaxHp();
}

int Player::getShieldCurrentHp(){
    return attributes->getShieldCurrentHp();
}

int Player::getShieldMaxHp(){
    return attributes->getShieldMaxHp() + this->userItem->getShieldMaxHp();
}

int Player::getCurrentLevel(){
    return this->level->getCurrentLevel();
}

int Player::getCurrentExp(){
    return this->level->getCurrentExp();
}

int Player::getStrength(){
    return this->attributes->getStrength() + this->userItem->getStrength();
}

int Player::getDefense(){
    return this->attributes->getDefense() + this->userItem->getDefense();
}

int Player::getDexterity(){
    return this->attributes->getDexterity() + this->userItem->getDexterity();
}

int Player::getVitality(){
    return this->attributes->getVitality() + this->userItem->getVitality();
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
    int totalDamage = this->getBaseDamage();
    CCARRAY_FOREACH(accumDamages, targetObject){
        damage = (CCInteger*) targetObject;
        totalDamage += damage->getValue();
    }
    return totalDamage;
}


bool Player::hasPlayerLog(){
    return (playerLog->count() != 0);
}

void Player::addExp(int addedExp){
    CCLOG("Player::addExp: %d", addedExp);
    levelUpCount += this->level->addExp(addedExp);
    CCLOG("Player::after addExp: levelUpCount%d", levelUpCount);
}

void Player::addItem(UserItem* getItem){
    this->getUserItem()->add(getItem->getType(), getItem->getItemId());
    this->addPlayerLog((getItem->getName() + "を手に入れた").c_str());
}

void Player::addPlayerLog(std::string text){
    playerLog->addObject(CCString::create(text));
}

std::string Player::popPlayerLog(){
    CCString* text = (CCString*) playerLog->lastObject();
    std::string retText = text->getCString();
    playerLog->removeLastObject();
    return retText;
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