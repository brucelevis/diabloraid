//
//  EnemyData.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#ifndef __diablo__EnemyData__
#define __diablo__EnemyData__

#include <iostream>
#include "EnemyMaster.h"
#include <map>
#include "Util.h"
using namespace std;

class EnemyData{
private:
    static int seqId;
    int getSeqId();
public:
    int id;
    int enemyId;
    int currentHp;
    static EnemyData* create(EnemyMaster* enemy);
    EnemyData(map<string, string> entity);
    ~EnemyData();
};

#endif /* defined(__diablo__EnemyData__) */