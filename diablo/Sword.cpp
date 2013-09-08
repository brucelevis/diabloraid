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

Sword::~Sword(){
}

