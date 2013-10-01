//
//  Shield.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Shield.h"
Shield::Shield(){
    _connectType = 3;
}

Shield* Shield::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Shield* sprite = new Shield();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Shield::~Shield(){
}

void Shield::actionRemoved(Player* player){
    player->shieldStatus->increase(player->getShieldRefill()->getValue());
}

