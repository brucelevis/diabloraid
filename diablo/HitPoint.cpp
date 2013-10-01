//
//  HitPoint.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#include "HitPoint.h"

HitPoint::HitPoint(int v){
    maxHp = v;
    currentHp = v;
}

HitPoint::~HitPoint(){
}

int HitPoint::getMaxHp(){
    return maxHp;
}

void HitPoint::increaseMaxHp(int v){
    this->setMaxHp(this->maxHp + v);
}

void HitPoint::decreaseMaxHp(int v){
    if((this->maxHp - v) < 0){
        this->setMaxHp(1);
        return;
    }
    this->setMaxHp(this->maxHp - v);
}

void HitPoint::setMaxHp(int v){
    maxHp = v;
    if(currentHp > v){
        currentHp = v; //maxHpが下がったときは、currentHpも合わせて下げる。
    }
}

int HitPoint::getCurrentHp(){
    return currentHp;
}

void HitPoint::setCurrentHp(int v){
    currentHp = v;
}

void HitPoint::increase(int v){
    int increasedValue = currentHp + v;
    if(increasedValue > maxHp){
        this->setCurrentHp(maxHp);
    } else {
        this->setCurrentHp(increasedValue);
    }
}

void HitPoint::reduce(int v){
    int reducedValue = currentHp - v;
    if(reducedValue < 0){
        this->setCurrentHp(0);
    } else {
        this->setCurrentHp(reducedValue);
    }
}

void HitPoint::recoverAll(){
    this->setCurrentHp(this->getMaxHp());
}

