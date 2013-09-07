//
//  Player.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//

#include "Player.h"

Player::Player(){
    hp = new HitPoint();
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