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

bool PanelSprite::isSamePanel(std::string panelName){
    return (this->getPanelName() == panelName);
}

bool PanelSprite::isNextPanel(PanelSprite* panel){
    //隣り合う条件は、上下左右斜め圏内にpanelが入っていること。
    //それぞれのミニマム値とマックス値
    float minX = this->getPositionX() - _size/2 - _size;
    float maxX = this->getPositionX() + _size/2 + _size;
    float minY = this->getPositionY() - _size/2 - _size;
    float maxY = this->getPositionY() + _size/2 + _size;
    
    return (minX <= panel->getPositionX() && maxX > panel->getPositionX() && minY <= panel->getPositionY() && maxY > panel->getPositionY());
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

int PanelSprite::getDirection(PanelSprite* panel){
    //後でクラスを作って移動する。
    double degrees = 180 / 3.14 * atan((panel->getPositionY() - this->getPositionY())
                                       / (panel->getPositionX() - this->getPositionX()));
    
    CCLog("degrees: %f", degrees);
    //CCLog("tan:%f", tan(3.14 / 4));
    //CCLog("atan:%f", 180 * atan(1) / 3.14);
    
    return 1;
}

void PanelSprite::setSize(float size){
    _size = size;
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
    this->setTextureRect(_frame->getRect(), false, CCSize(_size, _size));
}

void PanelSprite::setTouched(){
    //本当は、矢印をだす。
    //暫定で、タッチしたら、消灯するようにしている。
    this->_switchOn(false);
}

void PanelSprite::setUnTouched(){
    //本当は、矢印を消す。
    //暫定で、タッチしたら、消灯するようにしている。
    this->_switchOn(true);
}

void PanelSprite::switchOff(){
    this->_switchOn(false);
}

void PanelSprite::switchOn(){
    this->_switchOn(true);
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
