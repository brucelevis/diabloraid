//
//  Potion.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#include "Potion.h"
Potion::Potion(){
    _connectType = 2;
    _recoverNum  = 3;
}

Potion* Potion::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Potion* sprite = new Potion();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Potion::~Potion(){
}

//Playerのhpを回復する
void Potion::recover(Player *player){
    CCLog("recover");
    player->recover(_recoverNum);
}

void Potion::actionRemoved(Player* player){
    this->recover(player);
}