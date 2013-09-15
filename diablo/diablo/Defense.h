//
//  Defense.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__Defense__
#define __diablo__Defense__

#include <iostream>
class Defense{
    int max;
    int current;
    int brokenRate; //盾が破壊される確率
public:
    Defense(int v);
    ~Defense();
    int getMax();
    int getCurrent();
    void setCurrent(int v);
    void reduce(int v);
    void increase(int v);
    void damage(int v); //ダメージを受けたときに、defenseを下げるロジック。
};

#endif /* defined(__diablo__Defense__) */
