//
//  PotionRecover.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/17.
//
//

#include "PotionRecover.h"

PotionRecover::PotionRecover(int v){
    recoverNum = v;
}

PotionRecover::~PotionRecover(){
}

int PotionRecover::getValue(){
    return recoverNum;
}