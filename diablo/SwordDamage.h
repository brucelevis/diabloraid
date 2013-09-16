//
//  SwordDamage.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/16.
//
//

#ifndef __diablo__SwordDamage__
#define __diablo__SwordDamage__

#include <iostream>

class SwordDamage{
    int damage;
public:
    int getDamage();
    SwordDamage(int v);
    ~SwordDamage();
};

#endif /* defined(__diablo__SwordDamage__) */
