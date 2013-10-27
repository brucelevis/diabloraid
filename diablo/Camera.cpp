//
//  Camera.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/23.
//
//

#include "Camera.h"

Camera::Camera(CCPoint _position, CCRect _rect){
    position = _position;
    rect = _rect;
}

Camera::~Camera(){
}

bool Camera::intersectsRect(PanelSprite *panel){
    CCRect panelRect = panel->getRect();
    return rect.intersectsRect(panelRect);
}