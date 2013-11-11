//
//  EquipmentMasterManager.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/10.
//
//

#ifndef __diablo__EquipmentMasterManager__
#define __diablo__EquipmentMasterManager__

#include <iostream>
#include "ModelInstanceManager.h"
#include "ModelInterface.h"
#include "EquipmentMaster.h"
#include "cocos2d.h"
#include "Util.h"
using namespace cocos2d;

class EquipmentMasterManager : public ModelInstanceManager{
private:
public:
    ModelInterface* getByPrimaryKey(int id);
    EquipmentMasterManager();
    ~EquipmentMasterManager();
};
#endif /* defined(__diablo__EquipmentMasterManager__) */
