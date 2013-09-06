//
//  HitPoint.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#ifndef __diablo__HitPoint__
#define __diablo__HitPoint__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class HitPoint{
    int maxHp;
    int currentHp;
public:
    int getMaxHp();
    int getCurrentHp();
    void setCurrentHp(int v);
    void reduce(int v);
    HitPoint();
    ~HitPoint(void);
};
#endif /* defined(__diablo__HitPoint__) */
