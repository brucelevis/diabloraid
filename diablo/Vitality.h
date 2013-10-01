//
//  Vitality.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__Vitality__
#define __diablo__Vitality__

#include <iostream>
#include "AttributeBase.h"

class Vitality : public AttributeBase {
public :
    int getCalculatedHp(int v);
    
    Vitality(int v);
    ~Vitality();
};

#endif /* defined(__diablo__Vitality__) */
