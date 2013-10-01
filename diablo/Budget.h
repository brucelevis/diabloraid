//
//  Budget.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__Budget__
#define __diablo__Budget__

#include <iostream>

class Budget{
    int current;
public:
    void add(int v);
    int getCurrent();
    Budget();
    ~Budget();
};

#endif /* defined(__diablo__Budget__) */