//
//  Panel.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/17.
//
//

#include "PanelSprite.h"

PanelSprite::PanelSprite(){
    _deltaY = 0;
    _willRemoved = false;
    _isOn = false;
    _directionSprites = CCArray::create();
    _displayedDirection = CCDictionary::create();
    _displayedDirection->retain();
    _directionSprites->retain();
}

PanelSprite::~PanelSprite(void){
}

std::string PanelSprite::getPanelName(){
    return _panelName;
}

bool PanelSprite::isConnectable(PanelSprite* panel){
    if(!panel) return false;
    return _connectType == panel->_connectType;
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
    //角度は以下で取得出来る(-90 - 90)
    float dx = panel->getPositionX() - this->getPositionX();
    float dy = panel->getPositionY() - this->getPositionY();
    double degrees = 180 / 3.14 * atan(dy / dx);
    // 0 - 359に変換
    if (dx >= 0 && dy >= 0){
    } else if ( dx >= 0 && dy < 0 ) {
        //第四象限だから 0: 360, -90: 270
        degrees += 360;
    } else {
        //第二と第三象限だから
        degrees  = 180 + degrees;
    }
    
    //return (int)floor(degrees + 0.5);
    switch ((int)floor(degrees + 0.5)) {
        case 0:
            return 6;
            break;
        case 45:
            return 3;
        case 90:
            return 2;
        case 135:
            return 1;
        case 180:
            return 4;
        case 225:
            return 7;
        case 270:
            return 8;
        case 315:
            return 9;
        case 360:
            return 6;
        default:
            return 3;
            break;
    }
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
}

void PanelSprite::setUnTouched(){
    //本当は、矢印を消す。
    //暫定で、タッチしたら、消灯するようにしている。
}

void PanelSprite::switchOff(){
    this->_switchOn(false);
}

void PanelSprite::update(){
    //overrideする。
    //this->_switchOn(true);
    this->_switchOn(true);
}

void PanelSprite::actionGotoRemoved(Player* player){
    //overrideする。
}

void PanelSprite::actionRemoved(Player* player){
    //overrideする。
}

void PanelSprite::actionTouched(Player* player){
    //何回呼ばれても同じになるように作る。
}

void PanelSprite::actionUntouched(Player* player){
}

void PanelSprite::switchOn(){
    this->_switchOn(true);
}

void PanelSprite::pushDirectionSprite(int direction){
    //同じ方向のものは一つで十分
    if(_displayedDirection->objectForKey(direction)){
        return;
    }
    int arrowDirectionInt = this->hasArrow();
    if(arrowDirectionInt > 0){
        //矢印がある時は、削除してから、pushする。
        CCSprite* arrowDirection = (CCSprite*) _displayedDirection->objectForKey(arrowDirectionInt);
        this->removeChild(arrowDirection, true);
        arrowDirection->release();
        _displayedDirection->removeObjectForKey(arrowDirectionInt);
    }
    
    CCString* directionFileName = CCString::createWithFormat("%i.png",direction);
    CCSprite* directionSprite   =
        CCSprite::createWithSpriteFrameName(directionFileName->getCString());
    directionSprite->setPosition(CCPoint(_size/2, _size/2));
    _directionSprites->addObject(directionSprite);
    this->addChild(directionSprite);
    _displayedDirection->setObject(directionSprite, direction);
}

void PanelSprite::popDirectionSprite(){
}

int PanelSprite::hasArrow(){
    CCArray* arrowIntegers = CCArray::create();
    arrowIntegers->addObject(new CCInteger(15));
    arrowIntegers->addObject(new CCInteger(25));
    arrowIntegers->addObject(new CCInteger(35));
    arrowIntegers->addObject(new CCInteger(45));
    arrowIntegers->addObject(new CCInteger(65));
    arrowIntegers->addObject(new CCInteger(75));
    arrowIntegers->addObject(new CCInteger(85));
    arrowIntegers->addObject(new CCInteger(95));
    
    CCObject* targetObject    = NULL;
    CCInteger* integer        = NULL;
    int retVal          = 0;
    CCARRAY_FOREACH(arrowIntegers, targetObject){
        integer = (CCInteger*) targetObject;
        if(_displayedDirection->objectForKey(integer->getValue())){
            retVal = integer->getValue();
        };
    }
    return retVal;
}

void PanelSprite::removeAllDirectionSprite(){
    CCSprite* directionSprite = NULL;
    CCObject* targetObject    = NULL;
    
    CCARRAY_FOREACH(_directionSprites, targetObject){
        directionSprite = (CCSprite*) targetObject;
        this->removeChild(directionSprite, true);
    }
    _directionSprites->removeAllObjects();
    _displayedDirection->removeAllObjects();
}

void PanelSprite::setRemoved(Player* player){
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
