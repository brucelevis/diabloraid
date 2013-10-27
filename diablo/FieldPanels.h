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
#include "Floor.h"
#include "PanelSpriteFactory.h"
#include "FieldModel.h"
#include "ModelManager.h"
#include "PanelDataManager.h"

class FieldPanels : public CCArray{
    const float PANEL_SIZE = 64;
    const float PANEL_SCALE = 0.8;
    const float OFFSET_Y = 96;
    CCDictionary* _panelCount; //パネルの種類ごとにパネルをカウントする。
    FieldModel* _fieldModel;
    CCArray* _removedPanels;
    bool _moveState;
    bool _onMovingEndCalling = false;
    PanelSprite* createPanel(Floor* floor, int indexX, int indexY);
    PanelSprite* loadPanel(int indexX, int indexY);
public:
    static CCArray* create();
    static CCArray* createWithFieldModel(FieldModel* fieldModel);
    
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
    CCArray* getRemovedPanels();
    void setRemovedPanel(CCPoint* point);
    void refresh();
    void save();
    void update();
    void onMovingEnd();
    FieldPanels(FieldModel* fieldModel);
    ~FieldPanels();
};

#endif /* defined(__diablo__FieldPanels__) */
