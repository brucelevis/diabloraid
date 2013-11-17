//
//  UsableDetail.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/16.
//
//

#ifndef __diablo__UsableDetail__
#define __diablo__UsableDetail__

#include <iostream>
#include "cocos2d.h"
#include "DetailBase.h"
#include "UserItem.h"
#include "Player.h"

using namespace cocos2d;

class UsableDetail: public DetailBase{
    CCMenuItemSprite* pUseButton;
    UserItem* userItem;
    Player* player;
public:
    static UsableDetail* createWithUserItemAndPlayer(UserItem* userItem, Player* player);
    void addWindowObjects();
    void update();
    void use();
    UsableDetail(UserItem* userItem, Player* player);
    ~UsableDetail();
};

#endif /* defined(__diablo__UsableDetail__) */
