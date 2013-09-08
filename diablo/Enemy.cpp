//
//  Enemy.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#include "Enemy.h"

Enemy::Enemy(){
    hp = new HitPoint();
    _connectType = 1;
    strength = 5;
}

Enemy* Enemy::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Enemy* sprite = new Enemy();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Enemy::~Enemy(){
    
}

void Enemy::attack(Player* player){
    CCLog("strength:%d", strength);
    player->damage(strength);
}