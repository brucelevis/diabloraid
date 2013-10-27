//
//  FloorFloorFieldModel.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/27.
//
//

#include "FloorFieldModel.h"

static int WIDTH   = 36;
static int HEIGHT  = 36;
FloorFieldModel::FloorFieldModel(){
}

FloorFieldModel::~FloorFieldModel(){
    
}

int FloorFieldModel::getWidth(){
    return WIDTH;
}

int FloorFieldModel::getHeight(){
    return HEIGHT;
}

void FloorFieldModel::set(int x, int y, int panelId){
    CCAssert((x >=0 && x <= WIDTH && y <= HEIGHT && y >= 0), "x, y must be from 0 to max Size");
    
    CCDictionary* _dictionary = (CCDictionary*) this->objectForKey(x);
    if(_dictionary){
        _dictionary->setObject(CCInteger::create(panelId), y);
    } else {
        _dictionary = CCDictionary::create();
        _dictionary->retain();
        this->setObject((CCObject*) _dictionary, x);
        _dictionary->setObject(CCInteger::create(panelId), y);
    }
}

int FloorFieldModel::get(int x, int y){
    CCAssert((x >=0 && x <= WIDTH && y <= HEIGHT && y >= 0), "x, y must be from 0 to max Size");
    
    CCDictionary* _dictionary = (CCDictionary*) this->objectForKey(x);
    if(_dictionary){
        CCInteger* panelId = (CCInteger*) _dictionary->objectForKey(y);
        if(panelId){
            return panelId->getValue();
        }
    }
    //セットされていない時は-1を返す。
    return -1;
}

FieldModel* FloorFieldModel::getByIndex(int x, int y){
    int fieldWidth  = FieldModel::getWidth();
    int fieldHeight = FieldModel::getHeight();
    int startX = MIN(x, WIDTH - fieldWidth + 1);
    int startY = MIN(y, HEIGHT - fieldHeight + 1);
    FieldModel* fieldModel = FieldModel::create();
    fieldModel->retain();
    int i, j;
    for (i = 0; i <= fieldWidth; i++){
        for (j = 0; j <= fieldHeight; j++){
            fieldModel->set(i, j, this->get(i + startX, j + startY));
        }
    }
    return fieldModel;
}

FloorFieldModel* FloorFieldModel::create(){
    FloorFieldModel* pRet = new FloorFieldModel();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

void FloorFieldModel::setMockData(){
    for(int i = 0; i <= WIDTH; i++){
        for( int j = 0; j <= HEIGHT; j++){
            this->set(i, j, (rand() % 6));
        }
    }
}