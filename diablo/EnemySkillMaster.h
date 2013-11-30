//
//  EnemySkillMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/30.
//
//

#ifndef __diablo__EnemySkillMaster__
#define __diablo__EnemySkillMaster__

#include <iostream>
#include "picojson.h"
#include "Util.h"
#include "cocos2d.h"

using namespace cocos2d;

class EnemySkillMaster{
    picojson::value _records;
    int id;
    std::string name;
    int value;
    int imageId;
public:
    static EnemySkillMaster* getById(int v);
    std::string getName();
    int getId();
    int getValue();
    int getImageId();
    EnemySkillMaster(int v);
    ~EnemySkillMaster();
};

#endif /* defined(__diablo__EnemySkillMaster__) */
