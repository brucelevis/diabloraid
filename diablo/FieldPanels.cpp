//
//  FieldPanels.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/15.
//
//

#include "FieldPanels.h"
FieldPanels::FieldPanels(){
}

FieldPanels::~FieldPanels(){
}

void FieldPanels::add(PanelSprite* panel){
    this->addCount(panel);
    this->addObject((CCObject*) panel);
}

void FieldPanels::remove(int index){
    PanelSprite* panel = (PanelSprite*) this->objectAtIndex(index);
    this->decreaseCount(panel);
    this->removeObjectAtIndex(index);
}

void FieldPanels::initialize(){
    _panelCount = CCDictionary::create();
    _panelCount->retain();
}

int FieldPanels::getCurrentPanelNum(PanelSprite* panel){
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        return count->getValue();
    } else {
        return 0;
    }
}

void FieldPanels::addCount(PanelSprite* panel){
    //パネルの名前ごとにカウントする。
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        count->getValue();
        _panelCount->setObject(CCInteger::create(count->getValue()+1), panel->getPanelName());
    } else {
        _panelCount->setObject(CCInteger::create(1), panel->getPanelName());
    }
}

void FieldPanels::decreaseCount(PanelSprite* panel){
    //パネルの名前ごとにカウントする。
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        count->getValue();
        _panelCount->setObject(CCInteger::create(count->getValue()-1), panel->getPanelName());
    } else {
        CCLog("assert impossible!!!");
    }
}

PanelSprite* FieldPanels::createPanel(Floor* floor, int indexX, int indexY, float size,float scale){
    CCString* panelName = floor->createPanelName();
    PanelSprite* pSprite = this->createPanelSprite(panelName->getCString(), floor);
    //追加出来ないパネルだったら。
    if(!pSprite->canBeAdded(this->getCurrentPanelNum(pSprite))){
        pSprite->release();
        return this->createPanel(floor, indexX, indexY, size, scale);
    }
    
    pSprite->setSize(size);
    pSprite->setContentSize(CCSize(size,size));
    pSprite->setScale(scale);
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size/2 + size * indexX, 96 + size/2 + size * indexY) );
    pSprite->update();
    return pSprite;
}

PanelSprite* FieldPanels::createPanelSprite(std::string panelName, Floor* floor){
    PanelSprite* pSprite;
    if(panelName == "enemy"){
        pSprite = EnemyFactory::getEnemyPanel(floor);
    } else if(panelName == "potion"){
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "sword"){
        pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "coin"){
        pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "shield"){
        pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "kaidan"){
        pSprite = Stair::createWithSpriteFrameName(panelName.c_str());
    } else {
        pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
    }
    return pSprite;
}
