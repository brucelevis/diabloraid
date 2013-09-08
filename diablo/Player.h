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
    CCArray* accumDamages; //パネルをタッチしている間の累積ダメージを保存する。push popで簡単に処理するため
public:
    HitPoint* hp;
    void damage(int v);
    void recover(int v);
    bool isAlive();
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
    int getTotalDamage(); //今回の累積ダメージを取得する。
    Player();
    ~Player(void);
};
#endif /* defined(__diablo__Player__) */
