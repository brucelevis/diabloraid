//
//  BaseDamage.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "BaseDamage.h"

BaseDamage::BaseDamage(int v){
    value = v;
}

BaseDamage::~BaseDamage(){
}

int BaseDamage::getValue(){
    return value;
}
