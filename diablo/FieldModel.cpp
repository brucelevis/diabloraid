//
//  FieldModel.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/12.
//
//

#include "FieldModel.h"



FieldModel::FieldModel(){
}

FieldModel::~FieldModel(){
    
}

void FieldModel::set(int x, int y, int panelId){
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

int FieldModel::get(int x, int y){
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

CCString* FieldModel::getPanelName(int x, int y){
    return this->convertToPanelName(this->get(x, y));
}

CCString* FieldModel::convertToPanelName(int panelType){
    CCDictionary* _panelNameMap = CCDictionary::create();

    _panelNameMap->setObject((CCObject*) new CCString("coin"), 0);
    _panelNameMap->setObject((CCObject*) new CCString("enemy"), 1);
    _panelNameMap->setObject((CCObject*) new CCString("shield"), 2);
    _panelNameMap->setObject((CCObject*) new CCString("sword"), 3);
    _panelNameMap->setObject((CCObject*) new CCString("potion"), 4);
    _panelNameMap->setObject((CCObject*) new CCString("kaidan"), 5);
    _panelNameMap->setObject((CCObject*) new CCString(""), -1);
    return (CCString*) _panelNameMap->objectForKey(panelType);
}

int FieldModel::convertToPanelType(std::string panelName){
    CCDictionary* _panelNameMap = CCDictionary::create();

    _panelNameMap->setObject((CCObject*) new CCInteger(0), "coin");
    _panelNameMap->setObject((CCObject*) new CCInteger(1), "enemy");
    _panelNameMap->setObject((CCObject*) new CCInteger(2), "shield");
    _panelNameMap->setObject((CCObject*) new CCInteger(3), "sword");
    _panelNameMap->setObject((CCObject*) new CCInteger(4), "potion");
    _panelNameMap->setObject((CCObject*) new CCInteger(5), "kaidan");
    _panelNameMap->setObject((CCObject*) new CCInteger(-1), "");
    return ((CCInteger*) _panelNameMap->objectForKey(panelName))->getValue();
}

FieldModel* FieldModel::create(){
    FieldModel* pRet = new FieldModel();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

void FieldModel::setMockData(){
    for(int i = 0; i <= WIDTH; i++){
        for( int j = 0; j <= HEIGHT; j++){
            this->set(i, j, (rand() % 6));
        }
    }
}