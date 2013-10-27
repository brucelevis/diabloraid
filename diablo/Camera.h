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

using namespace cocos2d;

class Camera {
    CCPoint position; //座標
    CCRect  rect;     //大きさ
    CCRect viewRect;  //相対位置のviewRect
    float dx;
    float dy;
    bool onMoving;    //動いているとき。
public:
    bool intersectsRect(PanelSprite* panel); // panelがカメラの中に入っているかどうかを判定する。
    void update();
    void showPanels();                       // cameraに入っているパネル
    void move();
    void setMove(bool isOnMove);
    CCPoint* getPosition();
    void setPosition(float x, float y);
    Camera(CCPoint position, CCRect rect);
    ~Camera();
};

#endif /* defined(__diablo__Camera__) */
