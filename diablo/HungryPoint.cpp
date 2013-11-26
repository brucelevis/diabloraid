//
//  HungryPoint.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/27.
//
//

#include "HungryPoint.h"

HungryPoint::HungryPoint(int v){
    max = v;
    current = v;
}

HungryPoint::~HungryPoint(){
}

int HungryPoint::getMax(){
    return max;
}

void HungryPoint::increaseMax(int v){
    this->setMax(this->max + v);
}

void HungryPoint::decreaseMax(int v){
    if((this->max - v) < 0){
        this->setMax(1);
        return;
    }
    this->setMax(this->max - v);
}

void HungryPoint::setMax(int v){
    max = v;
    if(current > v){
        current = v; //maxが下がったときは、currentも合わせて下げる。
    }
}

int HungryPoint::getCurrent(){
    return current;
}

void HungryPoint::setCurrent(int v){
    current = v;
}

void HungryPoint::increase(int v){
    int increasedValue = current + v;
    if(increasedValue > max){
        this->setCurrent(max);
    } else {
        this->setCurrent(increasedValue);
    }
}

void HungryPoint::reduce(int v){
    int reducedValue = current - v;
    if(reducedValue < 0){
        this->setCurrent(0);
    } else {
        this->setCurrent(reducedValue);
    }
}

void HungryPoint::recoverAll(){
    this->setCurrent(this->getMax());
}
