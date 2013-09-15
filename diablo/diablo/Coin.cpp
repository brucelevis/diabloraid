//
//  Coin.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Coin.h"

Coin::Coin(){
    _connectType = 4;
}

Coin* Coin::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Coin* sprite = new Coin();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Coin::~Coin(){
}

