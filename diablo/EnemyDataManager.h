//
//  EnemyDataManager.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/27.
//
//

#ifndef __diablo__EnemyDataManager__
#define __diablo__EnemyDataManager__

#include <iostream>
#include "ModelInstanceManager.h"
#include "EnemyData.h"
#include "cocos2d.h"
#include "Util.h"
using namespace cocos2d;

class EnemyDataManager : public ModelInstanceManager{
private:
public:
    EnemyDataManager();
    ~EnemyDataManager();
};

#endif /* defined(__diablo__EnemyDataManager__) */
