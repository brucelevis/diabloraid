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
using namespace cocos2d;

class Field {
    const float PANEL_SIZE = 64;
    const float PANEL_SCALE = 0.8;
    CCLayer* _parentLayer;
    Player* _player;
    CCArray* _panelNames;
    CCArray* _panels;
    CCArray* _removedPanels;
    TouchedPanels* _touchedPanels; //タッチされたパネルを順に格納する。
    PanelSprite* _currentPanel;
    std::string _touchedPanelName;
    PanelSprite* _connectPanel;
    bool _moveState;
public:
    Field(CCLayer *parentLayer, Player* player);
    ~Field(void);
    
    CCArray* createInitialField();
    CCArray* getPanels();
    CCArray* getWillBeRemovedPanel(); //今回消えるパネルを取得する。
    CCArray* getEnemies();
    void onTouchMove(CCTouch* touch);
    void onTouchStart(CCTouch* touch);
    void onTouchEnd(CCTouch* touch);
    void showDirections(); //今まさに消えんとしているパネルの上に、方向を表示する。
    bool getOnTurn();
    void onTurnStart();
    void onTurnEnd();
    CCArray* getRemovedPanels();
    void setRemoved();
    void setRemovedPanel(CCPoint* point);
    void setMoves();
    PanelSprite* createPanel(int indexX, int indexY);
    PanelSprite* createPanelSprite(std::string panelName);
    void removePanels();
    void restockPanels();
    void movePanels();
    void closeUp();
    void cleanUp(); //全パネルをなめて、上にのっている方向spriteを削除する。
};

#endif /* defined(__diablo__Field__) */
