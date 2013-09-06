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
#include "Field.h"
#include "Player.h"

using namespace cocos2d;

class TurnManager {
    int *_turn;
    Field* _field;
    Player* _player;
public:
    TurnManager(Field* field, Player* player);
    ~TurnManager(void);
    int getTurn();
    void attack(CCArray* enemies);
    void start();
    void end();
};


#endif /* defined(__diablo__TurnManager__) */

