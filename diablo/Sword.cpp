//
//  Sword.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Sword.h"


Sword::Sword(){
    _connectType = 1;
    _alreadyActionTouched = false;
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
    if(_alreadyActionTouched){
        return;
    }
    player->pushDamage(player->getSwordDamage()->getDamage());
    _alreadyActionTouched = true;
}

// override
// タッチが外れたときにやること:playerのaccumDamageをpop
void Sword::actionUntouched(Player* player){
    player->popDamage();
    _alreadyActionTouched = false;
}

Sword::~Sword(){
}

