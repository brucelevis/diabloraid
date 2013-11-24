//
//  TreasureFactory.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/24.
//
//

#ifndef __diablo__TreasureFactory__
#define __diablo__TreasureFactory__

#include <iostream>
#include "Floor.h"
#include "UserItem.h"
#include "ItemMapMaster.h"
#include <map>

using namespace std;

class TreasureFactory {
public:
    static UserItem* createTreasure();
};

#endif /* defined(__diablo__TreasureFactory__) */
