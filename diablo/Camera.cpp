//
//  Camera.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/23.
//
//

#include "Camera.h"

Camera::Camera(CCPoint _position, CCRect _rect){
    dx = 0;
    dy = 0;
    onMoving = false;
    
    rect = _rect;
    position  = _position;
    //position = ccp(_position.x + rect.getMinX(), _position.y + rect.getMinY());
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
    viewRect.setRect(x + rect.getMinX(), y + rect.getMinY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY());
    position.setPoint(x, y);
}

void Camera::setMoveVector(CCPoint vector){
    dx = vector.x;
    dy = vector.y;
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
        CCLOG("STOP");
        onMoving = false;
        return;
    }
    CCLOG("MOVE");
    float currentX = this->getPosition()->x;
    float currentY = this->getPosition()->y;
    this->setPosition(currentX + 5.12, currentY);
    //this->setPosition(currentX, currentY);
    
    dx -= 5.12;
}