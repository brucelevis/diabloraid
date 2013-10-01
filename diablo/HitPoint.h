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

class HitPoint{
    int maxHp;
    int currentHp;
public:
    int getMaxHp();
    int getCurrentHp();
    void setCurrentHp(int v);
    void reduce(int v);
    void increase(int v);
    void recoverAll(); //hpを全回復する。
    HitPoint(int v);
    ~HitPoint(void);
};
#endif /* defined(__diablo__HitPoint__) */
