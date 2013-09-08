//
//  Sword.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Sword.h"


Sword::Sword(){
    damageValue = 20;
    _connectType = 1;
}

Sword* Sword::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Sword* sprite = new Sword();
    
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
// タッチされたときにやること:playerのaccumDamageに追加
void Sword::actionTouched(Player* player){
    player->pushDamage(damageValue);
}

// override
// タッチが外れたときにやること:playerのaccumDamageをpop
void Sword::actionUntouched(Player* player){
    player->popDamage();
}

Sword::~Sword(){
}

