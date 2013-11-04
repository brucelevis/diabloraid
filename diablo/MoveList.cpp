//
//  MoveList.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/03.
//
//

#include "MoveList.h"

void MoveList::push(MoveVector* vector){
    this->addObject((CCObject*) vector);
}

void MoveList::pop(){
    this->removeLastObject();
}

void MoveList::handle(MoveInterface* moveObject){
    CCLOG("handle");
    MoveVector* moveVector = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this, targetObject){
        moveVector = (MoveVector*) targetObject;
        if(moveVector->move(moveObject)){
            CCLOG("move");
            return;
        };
    }
}