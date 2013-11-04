//
//  Camera.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/23.
//
//

#ifndef __diablo__Camera__
#define __diablo__Camera__

#include <iostream>
#include "cocos2d.h"
#include "PanelSprite.h"
#include "MoveInterface.h"
#include "MoveVector.h"
#include "MoveList.h"

using namespace cocos2d;


class Camera : MoveInterface{
    CCPoint position; //座標
    CCRect  rect;     //大きさ
    CCRect viewRect;  //相対位置のviewRect
    float dx;
    float dy;
    
    MoveVector moveVector;
    MoveList* moveList;
    
    bool onMoving;
    bool onMovingX;    //X方向に動いているとき。
    bool onMovingY;    //Y方向に動いている時。
public:
    bool intersectsRect(PanelSprite* panel); // panelがカメラの中に入っているかどうかを判定する。
    void update();
    void showPanels();                       // cameraに入っているパネル
    void move();
    void move(float x, float y);
     
    void setMove(bool isOnMove);
    CCPoint* getPosition();
    void setPosition(float x, float y);
    void setMoveVector(MoveVector* vector);
    Camera(CCPoint position, CCRect rect);
    ~Camera();
};

#endif /* defined(__diablo__Camera__) */
