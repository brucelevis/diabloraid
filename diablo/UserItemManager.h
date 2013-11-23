//
//  UserItemManager.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/23.
//
//

#ifndef __diablo__UserItemManager__
#define __diablo__UserItemManager__


#include <iostream>
#include "ModelInstanceManager.h"
#include "ModelInterface.h"
#include "UserItem.h"
#include "cocos2d.h"
#include "Util.h"
using namespace cocos2d;

class UserItemManager : public ModelInstanceManager{
private:
public:
    UserItemManager();
    ~UserItemManager();
};


#endif /* defined(__diablo__UserItemManager__) */
