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
#include "MainGameScene.h"

using namespace cocos2d;
class MainGameScene;

class TurnManager {
    int *_turn;
    Field* _field;
    Player* _player;
    MainGameScene* _layer;
public:
    TurnManager(MainGameScene* layer, Field* field, Player* player);
    ~TurnManager(void);
    int getTurn();
    void actionGotoRemoved(CCArray* removedPanels); //消えないときも触れられていたときに何かするならここで。
    void actionRemoved(CCArray* removedPanels); //消えるときに何かするならここで。
    void attack(CCArray* enemies);
    void start();
    void gameOver();
    void turnEnd();
    void end();
};


#endif /* defined(__diablo__TurnManager__) */

