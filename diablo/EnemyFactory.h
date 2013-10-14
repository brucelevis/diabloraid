//
//  EnemyFactory.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#ifndef __diablo__EnemyFactory__
#define __diablo__EnemyFactory__

#include <iostream>
#include "EnemyMaster.h"
#include "Floor.h"
#include "FloorEnemyMapMaster.h"
#include "EnemyData.h"

class EnemyFactory{
public:
    static EnemyMaster* createEnemy(Floor* floor); //エネミーパネルを生成して返す。
};

#endif /* defined(__diablo__EnemyFactory__) */
