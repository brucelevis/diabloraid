//
//  Panel.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/17.
//
//

#include "PanelSprite.h"

PanelSprite::PanelSprite(void){
    _deltaY = 0;
}

PanelSprite::~PanelSprite(void){
}

PanelSprite* PanelSprite::createWithSpriteFrameName(const char *pszSpriteFrameName){
    PanelSprite* sprite = new PanelSprite();
    if(sprite && sprite->initWithSpriteFrameName(pszSpriteFrameName)){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void PanelSprite::setDeltaY(float deltaY){
    _deltaY = deltaY;
    this->_velocity = _deltaY / 100 * 10;
}

void PanelSprite::setPosition(const CCPoint& pos){
    this->CCSprite::setPosition(pos);
    CCSize size = this->getContentSize();
    this->_touchRect.setRect(pos.x - size.width/2 + 1, pos.y - size.height/2 + 1, size.width - 2, size.height - 2);    
}

//移動量に合わせて移動させて、deltaXを減らす。
bool PanelSprite::move(){
    if (_deltaY >= -0.0001 && _deltaY <= 0.0001 ){
        return false;
    }
    float currentY = this->getPositionY();
    this->setPositionY(currentY - _velocity);
    _deltaY -= _velocity;
    return true;
}

//タッチ領域の取得
CCRect PanelSprite::getTouchRect(){
    return _touchRect;
}
