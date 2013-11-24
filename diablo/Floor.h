//
//  Floor.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/13.
//
//

#ifndef __diablo__Floor__
#define __diablo__Floor__

#include <iostream>
#include "cocos2d.h"
#include "PanelMapMaster.h"
using namespace cocos2d;

class Floor{
    int floor;
    int turn;
    int totalTurn;
public:
    int getTurn();
    int getFloor();
    void countupTurn(int v);  // vだけ、ターンを経過させる。
    void countupFloor(int v); //vだけフロアを進ませる。
    int createPanel();//どのパネルが出るのかをフロアのマスタ−情報、経過情報などから取得する。
    Floor(int v);
    ~Floor();
};

#endif /* defined(__diablo__Floor__) */
