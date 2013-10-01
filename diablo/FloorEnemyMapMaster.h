//
//  FloorEnemyMapMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__FloorEnemyMapMaster__
#define __diablo__FloorEnemyMapMaster__

#include <iostream>
#include "picojson.h"
#include "Util.h"
#include "cocos2d.h"
using namespace cocos2d;

class FloorEnemyMapMaster{
    picojson::value _records;
    CCArray* _enemies;
public:
    static FloorEnemyMapMaster* getById(int v);
    
    CCArray* getEnemies();
    FloorEnemyMapMaster(int v);
    ~FloorEnemyMapMaster();
};

#endif /* defined(__diablo__FloorEnemyMapMaster__) */
