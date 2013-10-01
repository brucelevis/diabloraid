//
//  Vitality.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "Vitality.h"

int Vitality::getCalculatedHp(){
    return this->current * 10;
}

Vitality::Vitality(int v) : AttributeBase(v){
}

Vitality::~Vitality(){
}