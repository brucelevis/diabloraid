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
#include "Camera.h"
#include "MoveVector.h"

using namespace cocos2d;
class MainGameScene;

class TurnManager {
    int *_turn;
    Field* _field;
    Player* _player;
    Camera* _camera;
    MainGameScene* _layer;
public:
    TurnManager(MainGameScene* layer, Field* field, Player* player, Camera* camera);
    ~TurnManager(void);
    int getTurn();
    void gotoNextFloor(CCArray* removedPanels);
    void actionGotoRemoved(CCArray* removedPanels); //消えないときも触れられていたときに何かするならここで。
    void actionRemoved(CCArray* removedPanels); //消えるときに何かするならここで。
    void setCameraMove(CCArray* removedPanels); //消える時に、cameraの移動をセットする。
    void attack(CCArray* enemies);
    void start();
    void progressTurn();
    void gameOver();
    void turnEnd();
    void end();
};


#endif /* defined(__diablo__TurnManager__) */

