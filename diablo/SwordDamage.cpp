//
//  SwordDamage.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/16.
//
//

#include "SwordDamage.h"

SwordDamage::SwordDamage(int v){
    damage = v;
}

SwordDamage::~SwordDamage(){
}

int SwordDamage::getDamage(){
    return damage;
}
