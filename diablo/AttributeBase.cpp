//
//  AttributeBase.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//  vitalityとかstrengthとかdefenseとかそういうベース。
//

#include "AttributeBase.h"

AttributeBase::AttributeBase(int v){
    current = v;
    max     = v;
}

AttributeBase::~AttributeBase(){
}

void AttributeBase::add(int v){
    current += v;
    max += v;
}

int AttributeBase::getCurrent(){
    return current;
}

void AttributeBase::decreaseCurrent(int v){
    this->setCurrent(current - v);
}

void AttributeBase::recoverAll(){
    this->current = max;
}

void AttributeBase::setCurrent(int v){
    int setValue = v;
    if(v < 0){
        setValue = 0;
    }
    if(v > max){
        setValue = max;
    }
    this->current = setValue;
}
