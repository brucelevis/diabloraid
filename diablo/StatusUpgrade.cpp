//
//  StatusUpgrade.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//  ステータスを上昇下降させるパーツ
//

#include "StatusUpgrade.h"

StatusUpgrade::~StatusUpgrade(){
}

StatusUpgrade::StatusUpgrade(){
}

StatusUpgrade* StatusUpgrade::createStatusLine(std::string name, int current, CCPoint position, int remain){
    StatusUpgrade* statusLine = new StatusUpgrade();
    statusLine->_current = current;
    statusLine->_currentAddition = 0;
    statusLine->setRemain(remain); //初期値
    
    statusLine->addElements(name, position);
    
    if(statusLine){
        statusLine->autorelease();
        return statusLine;
    }
    
    CC_SAFE_DELETE(statusLine);
    return NULL;
}

void StatusUpgrade::addElements(std::string name, CCPoint position){
    CCLabelTTF* strength = CCLabelTTF::create(name.c_str(), "Thonburi", 10);
    strength->setAnchorPoint(ccp(0,0.5));
    strength->setPosition(ccp(30, position.y));
    this->addChild(strength, 1);
    
    CCLabelTTF* currentLabel = CCLabelTTF::create(CCString::createWithFormat("%d", this->_current)->getCString(), "arial", 10);
    currentLabel->setAnchorPoint(ccp(0,0.5));
    currentLabel->setPosition(ccp(90, position.y));
    this->addChild(currentLabel);
    
    char* desc = this->getDescription(name);
    CCLabelTTF* description = CCLabelTTF::create(desc, "Thonburi", 8);
    description->setAnchorPoint(ccp(0,0.5));
    description->setPosition(ccp(35, position.y - 20));
    this->addChild(description);
    
    afterLabel   = CCLabelTTF::create(CCString::createWithFormat("-> %d", this->_current + this->_currentAddition)->getCString(), "arial", 10);
    afterLabel->setAnchorPoint(ccp(0, 0.5));
    afterLabel->setPosition(ccp(120, position.y));
    this->addChild(afterLabel);
    
    CCSprite* plus = CCSprite::createWithSpriteFrameName("plus.png");
    CCSprite* plusOff = CCSprite::createWithSpriteFrameName("plus.png");
    plusOff->setColor(ccc3(102,102,102));
    CCMenuItemSprite* pPlusButton =
        CCMenuItemSprite::create(plus, plusOff, this, menu_selector(StatusUpgrade::plus));
    
    CCSprite* minus = CCSprite::createWithSpriteFrameName("minus.png");
    CCSprite* minusOff = CCSprite::createWithSpriteFrameName("minus.png");
    minusOff->setColor(ccc3(102,102,102));
    CCMenuItemSprite* pMinusButton =
        CCMenuItemSprite::create(minus, minusOff, this, menu_selector(StatusUpgrade::minus));
    
    pPlusButton->setPosition(ccp(position.x - 90, position.y));
    pMinusButton->setPosition(ccp(position.x - 50, position.y));
    CCMenu* pMenu = CCMenu::create(pPlusButton, pMinusButton, NULL);
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu);
}

void StatusUpgrade::plus(){
    if( this->_remain == 0 ){
        return;
    }
    this->_currentAddition++;
    this->afterLabel->setString(CCString::createWithFormat("-> %d", this->_current + this->_currentAddition)->getCString());
    this->_remain--;
    CCLOG("plus: currentPoint:%d",this->_currentAddition);
}

void StatusUpgrade::minus(){
    if( this->_currentAddition == 0){
        return;
    }
    this->_currentAddition--;
    this->_remain++;
    this->afterLabel->setString(CCString::createWithFormat("-> %d", this->_current + this->_currentAddition)->getCString());
    CCLOG("minus: currentPoint:%d",this->_currentAddition);
}

void StatusUpgrade::setRemain(int remain){
    this->_remain = remain;
}

int StatusUpgrade::getCurrentAddition(){
    return this->_currentAddition;
}

char* StatusUpgrade::getDescription(std::string name){
    if(!strcmp(name.c_str(), "Strength")){
        return "ベースのダメージが上昇します";
    } else if(!strcmp(name.c_str(), "Defense")){
        return "盾回復量が上昇します。";
    } else if(!strcmp(name.c_str(), "Dexterity")){
        return "お金取得量が上昇します。";
    } else if(!strcmp(name.c_str(), "Vitality")){
        return "HPの上限値が上昇します";
    }
    return "";
}