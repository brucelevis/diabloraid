//
//  MoveVector.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/03.
//
//

#ifndef __diablo__MoveVector__
#define __diablo__MoveVector__

#include <iostream>
#include "cocos2d.h"
#include "MoveInterface.h"

using namespace cocos2d;

class MoveVector : public CCPoint {
    bool onMoving;
    CCPoint vector;
    CCPoint current;
    CCPoint velocity;
public:
    bool move(MoveInterface* moveObject);
    MoveVector(float x, float y);
    MoveVector();
    ~MoveVector();
};

#endif /* defined(__diablo__MoveVector__) */