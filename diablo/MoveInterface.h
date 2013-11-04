//
//  MoveInterface.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/03.
//
//

#ifndef __diablo__MoveInterface__
#define __diablo__MoveInterface__

#include <iostream>

class MoveInterface{
public:
    virtual void move(float x, float y) = 0;
    virtual ~MoveInterface(){};
};
#endif /* defined(__diablo__MoveInterface__) */