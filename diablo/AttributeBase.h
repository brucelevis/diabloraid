//
//  AttributeBase.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__AttributeBase__
#define __diablo__AttributeBase__

#include <iostream>

class AttributeBase {
protected:
    int current;//状態異常などで、一時的にcurrent != maxになるとき用
    int max;
public:
    void add(int v);
    int getCurrent();
    void decreaseCurrent(int v);
    void setCurrent(int v);
    void recoverAll();
    AttributeBase(int v);
    ~AttributeBase();
};
#endif /* defined(__diablo__AttributeBase__) */
