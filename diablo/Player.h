//
//  Player.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#ifndef __diablo__Player__
#define __diablo__Player__

#include <iostream>
#include "cocos2d.h"
#include "HitPoint.h"
using namespace cocos2d;

class Player{
public:
    HitPoint* hp;
    void damage(int v);
    void recover(int v);
    bool isAlive();
    Player();
    ~Player(void);
};
#endif /* defined(__diablo__Player__) */
