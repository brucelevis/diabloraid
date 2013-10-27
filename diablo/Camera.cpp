//
//  Camera.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/23.
//
//

#include "Camera.h"

Camera::Camera(CCPoint _position, CCRect _rect){
    dx = 51.2;
    dy = 51.2;
    onMoving = false;
    
    position = _position;
    rect = _rect;
    viewRect  = CCRectMake(position.x + rect.getMinX(), position.y + rect.getMinY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY() );
}

Camera::~Camera(){
}

bool Camera::intersectsRect(PanelSprite *panel){
    CCRect panelRect = panel->getRect();
    return viewRect.intersectsRect(panelRect);
}

CCPoint* Camera::getPosition(){
    return &position;
}

void Camera::setPosition(float x, float y){
    position.setPoint(x, y);
}

void Camera::setMove(bool isOnMove){
    onMoving = isOnMove;
}


void Camera::update(){
    if(!onMoving){
        return;
    }
    this->move();
}

void Camera::move(){
    if (this->dx >= -0.0001 && this->dx <= 0.0001 ){
        onMoving = false;
        return;
    }
    float currentX = this->getPosition()->x;
    float currentY = this->getPosition()->y;
    this->setPosition(currentX + 0.1, currentY);
    
    dx -= 0.1;
}