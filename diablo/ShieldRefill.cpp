//
//  ShieldRefill.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/17.
//
//

#include "ShieldRefill.h"
ShieldRefill::ShieldRefill(int v){
    value = v;
}

ShieldRefill::~ShieldRefill(){
}

int ShieldRefill::getValue(){
    return value;
}