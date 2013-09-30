//
//  EnemyMaster.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#ifndef __diablo__EnemyMaster__
#define __diablo__EnemyMaster__

#include <iostream>
#include "picojson.h"
#include "Util.h"

class EnemyMaster{
    picojson::value _records;
    int _id;
    std::string _name;
    int _hp;
    int _attack;
    int _def;
    int _exp;
public:
    static EnemyMaster* getById(int v);
    std::string getName();
    int getId();
    int getHp();
    int getAttack();
    int getDef();
    int getExp();
    EnemyMaster(int v);
    ~EnemyMaster();
};

#endif /* defined(__diablo__EnemyMaster__) */
