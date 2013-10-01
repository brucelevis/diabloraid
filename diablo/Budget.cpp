//
//  Budget.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "Budget.h"

Budget::Budget(){
    current = 0;
}

Budget::~Budget(){
}

void Budget::add(int v){
    current += v;
}

int Budget::getCurrent(){
    return current;
}