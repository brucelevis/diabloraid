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
    _willRemoved = false;
    _isOn = false;
}

PanelSprite::~PanelSprite(void){
}

std::string PanelSprite::getPanelName(){
    return _panelName;
}

PanelSprite* PanelSprite::createWithSpriteFrameName(const char *pszSpriteFrameName){
    PanelSprite* sprite = new PanelSprite();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void PanelSprite::_switchOn(bool isOn){
    std::string frameName;
    if(isOn){
        frameName = (this->_panelName + ".png").c_str();
        _isOn = true;
    } else {
        frameName = (this->_panelName + "_off.png").c_str();
        _isOn = false;
    }
    
    CCSpriteFrame* _frame;
    _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
    this->setTexture(_frame->getTexture());
    this->setTextureRect(_frame->getRect());
    this->setDisplayFrame(_frame);
}

void PanelSprite::setTouched(){
    //既にoff状態なら何もしない。
    if(!_isOn){
        return;
    }
    this->_switchOn(false);
}

void PanelSprite::setUnTouched(){
    //既にon状態なら何もしない。
    if(_isOn){
        return;
    }
    this->_switchOn(true);
}

void PanelSprite::setOff(){
    
}

void PanelSprite::setRemoved(){
    _willRemoved = true;
}

bool PanelSprite::isRemoved(){
    return _willRemoved;
}

void PanelSprite::setDeltaY(float deltaY){
    _deltaY += deltaY;
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
