//
//  Level.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#ifndef __diablo__Level__
#define __diablo__Level__

#include <iostream>
#include "LevelMaster.h"
class Level{
    int currentLevel;
    int exp;
public:
    Level();
    ~Level();
    int addExp(int addedExp); //経験値を上げて、レベルが上がった時は上がったレベルの差分を返す。
    int getCurrentLevel();
    int getCurrentExp();
};

#endif /* defined(__diablo__Level__) */