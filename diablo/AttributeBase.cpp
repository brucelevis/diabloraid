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