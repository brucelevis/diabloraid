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
    CCDictionary* _panelCount; //パネルの種類ごとにパネルをカウントする。
    FieldModel* _fieldModel;
public:
    static CCArray* create();
    void initialize(); //明示的に初期化処理を呼ぶ。
    void add(PanelSprite* panel); //パネルを追加する。
    void remove(int index); //inexのパネルを消す。
    void addCount(PanelSprite* panel);
    void decreaseCount(PanelSprite* panel);
    int getCurrentPanelNum(PanelSprite* panel);
    PanelSprite* createPanel(Floor* floor, int indexX, int indexY, float size, float scale);
    PanelSprite* createPanelSprite(std::string panelName, Floor* floor);
    FieldPanels();
    ~FieldPanels();
};

#endif /* defined(__diablo__FieldPanels__) */
