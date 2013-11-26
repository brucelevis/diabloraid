//
//  HungryPoint.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/27.
//
//

#ifndef __diablo__HungryPoint__
#define __diablo__HungryPoint__

#include <iostream>
class HungryPoint {
    int max;
    int current;
public:
    int getMax();
    int getCurrent();
    
    void increaseMax(int v);
    void decreaseMax(int v);
    void setMax(int v);
    void setCurrent(int v);
    void reduce(int v);
    void increase(int v);
    void recoverAll(); //hpを全回復する。
    HungryPoint(int v);
    ~HungryPoint(void);
};

#endif /* defined(__diablo__HungryPoint__) */
