//
//  MoveList.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/03.
//
//

#ifndef __diablo__MoveVectorList__
#define __diablo__MoveVectorList__

#include "cocos2d.h"
#include "MoveVector.h"
#include "MoveInterface.h"
using namespace cocos2d;

#include <iostream>

class MoveList : public CCArray {
public:
    void push(MoveVector* vector); // 移動vectorをpushする。
    void pop();                    // 移動vectorをpopする。
    void handle(MoveInterface* moveObject);                 // スタックされたvectorを順に処理していく。
};


#endif /* defined(__diablo__MoveList__) */