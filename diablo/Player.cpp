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
    CCLog("before_hp:%d", hp->getCurrentHp());
    hp->reduce(v);
    CCLog("after_hp:%d", hp->getCurrentHp());
}