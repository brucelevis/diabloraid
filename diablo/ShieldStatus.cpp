//
//  ShieldStatus.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "ShieldStatus.h"

ShieldStatus::ShieldStatus(int v){
    max = v;
    current = 0; //盾を取ると増えていく。
    brokenRate = 20; //とりあえず20%に置く
}

ShieldStatus::~ShieldStatus(){
}

int ShieldStatus::getMax(){
    return max;
}

int ShieldStatus::getCurrent(){
    return current;
}

void ShieldStatus::setCurrent(int v){
    current = v;
}

void ShieldStatus::increase(int v){
    int increased = current + v;
    if(increased > max){
        this->setCurrent(max);
    } else {
        this->setCurrent(increased);
    }
}

void ShieldStatus::reduce(int v){
    int reduced = current - v;
    if(reduced < 0){
        this->setCurrent(0);
    } else {
        this->setCurrent(reduced);
    }
}

// vのダメージを受けたときに、シールドがいくらすり減るか
void ShieldStatus::damage(int v){
    int i;
    int damaged = 0;
    // v回抽選
    for(i = 0; i < v; i++){
        // brokenRateよりも小さければ減る。
        if(rand() % 100 + 1 <= brokenRate){
            damaged++;
        }
    }
    this->reduce(damaged);
}