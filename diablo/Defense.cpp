//
//  Defense.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Defense.h"

Defense::Defense(int v){
    value = v;
}

Defense::~Defense(){
}

int Defense::getValue(){
    return value;
}
