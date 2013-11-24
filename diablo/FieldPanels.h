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
#include "FloorFieldModel.h"
#include "ModelManager.h"
#include "PanelDataManager.h"
#include "Camera.h"

class FieldPanels : public CCArray{
    const float PANEL_SIZE = 64;
    const float PANEL_SCALE = 0.8;
    const float OFFSET_Y = 96; //後でもっと上に持っていく。
    CCDictionary* _panelCount; //パネルの種類ごとにパネルをカウントする。
    Camera* camera;
    FloorFieldModel* _floorFieldModel;
    CCArray* _removedPanels;
    bool _moveState;
    bool _onMovingEndCalling = false;
    PanelSprite* createPanel(Floor* floor, int indexX, int indexY);
    PanelSprite* loadPanel(int indexX, int indexY);
public:
    static CCArray* create();
    static CCArray* createWithFloorFieldModel(FloorFieldModel* floorFieldModel, Camera* camera);
    
    void initialize(CCNode* parentNode, Floor* floor); //明示的に初期化処理を呼ぶ。
    void add(PanelSprite* panel); //パネルを追加する。
    void remove(int index); //inexのパネルを消す。
    void addCount(PanelSprite* panel);
    void decreaseCount(PanelSprite* panel);
    int getCurrentPanelNum(PanelSprite* panel);
    void removePanels();
    void removeAllPanels();
    void restockPanel(CCNode* parentNode, Floor* floor);
    void switchActiveState(); // cameraの表示領域に応じて active stateをon/offする。
    void setMoves();
    void movePanels();
    void adjustPosition();
    bool isMoving();
    CCArray* getRemovedPanels();
    //void setRemovedPanel(CCPoint* point);
    void setRemovedPanel(PanelSprite* panel);
    void refresh();
    void save();
    void update();
    void onMovingEnd();
    FieldPanels(FloorFieldModel* floorFieldModel, Camera* camera);
    ~FieldPanels();
};

#endif /* defined(__diablo__FieldPanels__) */
