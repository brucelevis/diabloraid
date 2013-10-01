//
//  BaseDamage.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__BaseDamage__
#define __diablo__BaseDamage__

#include <iostream>

class BaseDamage{
    int value;
public:
    BaseDamage(int v);
    ~BaseDamage();
    int getValue();
};

#endif /* defined(__diablo__BaseDamage__) */
