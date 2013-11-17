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

using namespace cocos2d;

class UsableDetail: public DetailBase{
    CCMenuItemSprite* pUseButton;
    UserItem* userItem;
public:
    static UsableDetail* createWithUserItem(UserItem* userItem);
    void addWindowObjects();
    void update();
    void use();
    UsableDetail(UserItem* userItem);
    ~UsableDetail();
};

#endif /* defined(__diablo__UsableDetail__) */
