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
    strength = new Strength(5);
    defense = new Defense(5);
    accumDamages = CCArray::create();
    accumDamages->retain();
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

// override
void Enemy::setRemoved(){
    // hpが今回の攻撃で0を下回る時だけ_willRemovedをたてる。
    if(hp->getCurrentHp() - this->getTotalDamage() <= 0){
        _willRemoved = true;
    }
}

// ダメージ増減ロジック
// つながっているパネルが剣敵A剣剣敵B剣とすると
// 剣敵まで来た時に、敵にダメージ
// 剣敵剣と来たときに、追加ダメージ
// 剣敵剣から敵に戻した時は、敵を回復
void Enemy::pushDamage(int v){
    accumDamages->addObject(CCInteger::create(v));
}

void Enemy::popDamage(){
    accumDamages->removeObject(accumDamages->lastObject());
}

void Enemy::resetDamage(){
    accumDamages->removeAllObjects();
}

int Enemy::getTotalDamage(){
    CCInteger* damage      = NULL;
    CCObject* targetObject = NULL;
    int totalDamage = 0;
    CCARRAY_FOREACH(accumDamages, targetObject){
        damage = (CCInteger*) targetObject;
        totalDamage += damage->getValue();
    }
    return totalDamage;
}


void Enemy::attack(Player* player){
    player->damage(strength->getValue());
}

Enemy::~Enemy(){
    delete strength;
    delete defense;
    delete hp;
}

