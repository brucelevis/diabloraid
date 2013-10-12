//
//  FieldPanels.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/15.
//
//

#ifndef __diablo__FieldPanels__
#define __diablo__FieldPanels__

#include <iostream>
#include "PanelSprite.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "Potion.h"
#include "Coin.h"
#include "Sword.h"
#include "Shield.h"
#include "Stair.h"
#include "Floor.h"
#include "FieldModel.h"

class FieldPanels : public CCArray{
    const float PANEL_SIZE = 64;
    const float PANEL_SCALE = 0.8;
    CCDictionary* _panelCount; //パネルの種類ごとにパネルをカウントする。
    FieldModel* _fieldModel;
    CCArray* _removedPanels;
    bool _moveState;
public:
    static CCArray* create();
    void initialize(CCNode* parentNode, Floor* floor); //明示的に初期化処理を呼ぶ。
    void add(PanelSprite* panel); //パネルを追加する。
    void remove(int index); //inexのパネルを消す。
    void addCount(PanelSprite* panel);
    void decreaseCount(PanelSprite* panel);
    int getCurrentPanelNum(PanelSprite* panel);
    void removePanels();
    void removeAllPanels();
    void restockPanel(CCNode* parentNode, Floor* floor);
    void setMoves();
    void movePanels();
    bool isMoving();
    PanelSprite* createPanel(Floor* floor, int indexX, int indexY, float size, float scale);
    PanelSprite* createPanelSprite(std::string panelName, Floor* floor);
    CCArray* getRemovedPanels();
    void setRemovedPanel(CCPoint* point);
    void refresh();
    FieldPanels();
    ~FieldPanels();
};

#endif /* defined(__diablo__FieldPanels__) */
