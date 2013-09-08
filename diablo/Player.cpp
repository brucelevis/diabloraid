//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    hp = new HitPoint();
    accumDamages = CCArray::create();
    accumDamages->retain();
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
    int totalDamage = 0;
    CCARRAY_FOREACH(accumDamages, targetObject){
        damage = (CCInteger*) targetObject;
        totalDamage += damage->getValue();
    }
    return totalDamage;
}
