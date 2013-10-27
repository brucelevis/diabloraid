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
    map<string, EnemyData*> *_modelMap;
    std::string name;
public:
    EnemyDataManager();
    ~EnemyDataManager();
    void add(EnemyData* enemyData);
    void remove(EnemyData* enemyData);
    std::string getModelName();
    EnemyData* getByPrimaryKey(int id);
};

#endif /* defined(__diablo__EnemyDataManager__) */
