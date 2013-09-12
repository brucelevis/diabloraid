//
//  Floor.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/13.
//
//

#include "Floor.h"

Floor::Floor(int v){
    current = v;
}

Floor::~Floor(){
}

void Floor::up(int v){
    current += v;
}
