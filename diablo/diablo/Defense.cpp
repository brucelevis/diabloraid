//
//  Defense.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "Defense.h"

Defense::Defense(int v){
    max = v;
    current = 0; //盾を取ると増えていく。
    brokenRate = 20; //とりあえず20%に置く
}

Defense::~Defense(){
}

int Defense::getMax(){
    return max;
}

int Defense::getCurrent(){
    return current;
}

void Defense::setCurrent(int v){
    current = v;
}

void Defense::increase(int v){
    int increased = current + v;
    if(increased > max){
        this->setCurrent(max);
    } else {
        this->setCurrent(increased);
    }
}

void Defense::reduce(int v){
    int reduced = current - v;
    if(reduced < 0){
        this->setCurrent(0);
    } else {
        this->setCurrent(reduced);
    }
}

// vのダメージを受けたときに、シールドがいくらすり減るか
void Defense::damage(int v){
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