//
//  Stair.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/12.
//
//

#include "Stair.h"
Stair::Stair(){
    _connectType = 5;
    _isActiveOnlyOnePanel = true;
    _canExistNum = 1;
}

Stair* Stair::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Stair* sprite = new Stair();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Stair::~Stair(){
}

bool Stair::canBeAdded(int num){
    if(_canExistNum == -1){
        return true;
    }
    if(num + 1 > _canExistNum){
        return false;
    }
    return true;
}
