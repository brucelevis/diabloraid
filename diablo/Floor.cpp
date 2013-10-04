//
//  Floor.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/13.
//
//

#include "Floor.h"

Floor::Floor(int v){
    floor = v;
    turn = 1;
    totalTurn = 1;
}

Floor::~Floor(){
}

int Floor::getTurn(){
    return turn;
}

int Floor::getFloor(){
    return floor;
}

void Floor::countupTurn(int v){
    turn += v;
    totalTurn +=v;
}

void Floor::countupFloor(int v){
    turn   = 1;
    floor += v;
}

CCString* Floor::createPanelName(){
    CCArray* _panelNames = CCArray::create();
    _panelNames->retain();
    
    _panelNames->addObject(new CCString("coin"));
    _panelNames->addObject(new CCString("enemy"));
    _panelNames->addObject(new CCString("shield"));
    _panelNames->addObject(new CCString("sword"));
    _panelNames->addObject(new CCString("potion"));
    _panelNames->addObject(new CCString("kaidan"));
    
    //5％ずつ階段が出る確率が上がる仮実装
    int panelNum = 5;
    if(rand() % 100 < turn * 3 / 7) {
        panelNum = 6;
    }
    CCLog("panelNum:%d", panelNum);
    
    CCString* panelName = (CCString*) _panelNames->objectAtIndex(rand() % panelNum);
    return panelName;
}
