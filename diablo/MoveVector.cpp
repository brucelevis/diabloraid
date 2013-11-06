//
//  MoveVector.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/03.
//
//

#include "MoveVector.h"


bool MoveVector::move(MoveInterface *moveObject){
    float diff = ccpDistance(*this, current);
    //現在位置と目的位置の差が0.0001以下なら止まる。
    if (diff >= -0.0001 && diff <= 0.0001 ){
        onMoving = false;
        return false;
    }
    onMoving = true;
    moveObject->move(velocity.x, velocity.y);
    current.setPoint(current.x + velocity.x, current.y + velocity.y); //currentを動かす。
    return true;
}

MoveVector::MoveVector(float x, float y){
    CCPoint::setPoint(x, y);
    velocity = CCPoint(this->x / 20, this->y / 20);
    current  = CCPoint(0, 0);
}

MoveVector::MoveVector(){
}

MoveVector::~MoveVector(){
}