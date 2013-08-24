//
//  TurnManager.h
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#ifndef __diablo__TurnManager__
#define __diablo__TurnManager__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class TurnManager {
    int *_turn;
public:
    TurnManager(void);
    ~TurnManager(void);
    int getTurn();
    void start();
    void end();
};


#endif /* defined(__diablo__TurnManager__) */

