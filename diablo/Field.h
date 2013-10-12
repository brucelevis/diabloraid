//
//  Field.h
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#ifndef __diablo__Field__
#define __diablo__Field__

#include <iostream>
#include "cocos2d.h"
#include "PanelSprite.h"
#include "Player.h"
#include "TouchedPanels.h"
#include "FieldPanels.h"
#include "Floor.h"
using namespace cocos2d;

class Field : CCNode {
    CCNode* _parentLayer;
    Player* _player;
    FieldPanels* _panels;
    Floor* _floor;
    TouchedPanels* _touchedPanels; //タッチされたパネルを順に格納する。
    PanelSprite* _currentPanel;
    std::string _touchedPanelName;
    PanelSprite* _connectPanel;
public:
    Field(Player* player);
    ~Field(void);
    
    void createInitialField();
    void removeAllPanels();
    CCArray* getPanels();
    TouchedPanels* getWillBeRemovedPanel(); //今回消えるパネルを取得する。
    CCArray* getEnemies();
    PanelSprite* getConnectPanel();
    int getTurn();
    int getFloor();
    void gotoNextFloor(); //次のフロアに移動する。
    void onTouchMove(CCTouch* touch);
    void onTouchStart(CCTouch* touch);
    void onTouchEnd(CCTouch* touch);
    void showDirections(); //今まさに消えんとしているパネルの上に、方向を表示する。
    bool getOnTurn();
    void onTurnStart();
    void updateAllPanels();
    void onTurnEnd();
    void countUpTurn();
    void setRemoved();
    void initialize();
    void setMoves();
    void removePanels();
    void restockPanels();
    void movePanels();
    void closeUp();
    void cleanUp(); //全パネルをなめて、上にのっている方向spriteを削除する。
};

#endif /* defined(__diablo__Field__) */
