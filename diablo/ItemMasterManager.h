//
//  ItemMasterManager.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/10.
//
//

#ifndef __diablo__ItemMasterManager__
#define __diablo__ItemMasterManager__

#include <iostream>
#include "ModelInstanceManager.h"
#include "ModelInterface.h"
#include "ItemMaster.h"
#include "cocos2d.h"
#include "Util.h"
using namespace cocos2d;

class ItemMasterManager : public ModelInstanceManager{
private:
public:
    ModelInterface* getByPrimaryKey(int id);
    ItemMasterManager();
    ~ItemMasterManager();
};

#endif /* defined(__diablo__ItemMasterManager__) */
