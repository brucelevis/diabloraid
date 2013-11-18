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
    onMoving   = false;
    moveList = (MoveList*) MoveList::create();
    moveList->retain();
    
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

void Camera::setMoveVector(MoveVector* vector){
    moveList->push(vector);
    //moveVector = vector;
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
    //moveVector.move(this);
    moveList->handle(this);
}

void Camera::move(float x, float y){
    CCLOG("camera move:(%f, %f)", x, y);
    float currentX = this->getPosition()->x;
    float currentY = this->getPosition()->y;
    float setX;
    float setY;
    setX = MIN(MAX(currentX + x, 0), 51.2 * 35 * 0.8);
    setY = MIN(MAX(currentY + y, 0), 51.2 * 35 * 0.8);
    CCLOG("%f", setY);
    
    this->setPosition(setX, setY);
}