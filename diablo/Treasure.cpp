//
//  Treasure.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/22.
//
//

#include "Treasure.h"

Treasure::Treasure(){
    _connectType = 5;
    _isActiveOnlyOnePanel = true;
}

Treasure::~Treasure(){
}

Treasure* Treasure::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Treasure* sprite = new Treasure();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Treasure* Treasure::createWithUserItem(UserItem* userItem){
    Treasure* sprite   = new Treasure();
    sprite->_panelName = "treasure";
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->userItem = userItem;
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void Treasure::actionRemoved(Player* player){
    player->addItem(this->userItem);
}