//
//  HitPoint.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#include "HitPoint.h"

HitPoint::HitPoint(){
    maxHp = 100;
    currentHp = 100;
}

int HitPoint::getMaxHp(){
    return maxHp;
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

