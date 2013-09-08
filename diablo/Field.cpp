//
//  Field.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#include "Field.h"
#include "PanelSprite.h"
#include "Enemy.h"
#include "Potion.h"
#include "Coin.h"
#include "Sword.h"
#include "Shield.h"
#include <math.h>

Field::Field(CCLayer* parentLayer, Player* player){
    this->_player = player;
    this->_parentLayer = parentLayer;
    this->_connectPanel = NULL; //初期化
    
    this->_panelNames = CCArray::create();
    this->_panelNames->retain();
    this->_touchedPanels = (TouchedPanels*) TouchedPanels::create();
    this->_touchedPanels->retain();
    
    this->_panelNames->addObject(new CCString("coin"));
    this->_panelNames->addObject(new CCString("skelton"));
    this->_panelNames->addObject(new CCString("shield"));
    this->_panelNames->addObject(new CCString("sword"));
    this->_panelNames->addObject(new CCString("potion"));
}

Field::~Field(void){
}


CCArray* Field::createInitialField(){
    _panels = CCArray::create();
    _panels->retain();
    _removedPanels = CCArray::create();
    _removedPanels->retain();
    for(int i = 0; i <= 5; i++){
        for( int j = 0; j <= 5; j++){
            PanelSprite* pSprite = this->createPanel(i, j);
            // add the sprite as a child to this layer
             _panels->addObject(pSprite);
        }
    }
    
    return _panels;
}

CCArray* Field::getEnemies(){
    CCArray* enemies = CCArray::create();
    
    PanelSprite* panel;
    CCObject* targetObject;
    CCARRAY_FOREACH(_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel->getPanelName() == "skelton"){
            enemies->addObject((CCObject*) panel);
        }
    }
    return enemies;
}

CCArray* Field::getPanels(){
    return _panels;
}

CCArray* Field::getWillBeRemovedPanel(){
    return _touchedPanels;
}


void Field::onTouchStart(CCTouch* touch){
    //動いている時はタッチ出来ない。
    if(_moveState){
        return;
    }
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        if(panel && panel->getTouchRect().containsPoint(tap)){
            _touchedPanelName = panel->getPanelName();
            _connectPanel = panel;
            _touchedPanels->push(panel, _player);
        }
    }
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel && panel->isConnectable(_connectPanel)){
            panel->switchOn();
        } else {
            panel->switchOff();
        }
    }
}

void Field::onTouchEnd(CCTouch* touch){
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    this->setRemoved();
    _touchedPanelName = "";//リセット
    _connectPanel = NULL; //リセット
}

void Field::onTouchMove(CCTouch* touch){
    //動いている時はタッチmove出来ない。
    if(_moveState){
        return;
    }
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        if(panel && panel->getTouchRect().containsPoint(tap)){
           if(panel->isConnectable(_connectPanel) && panel->isNextPanel((PanelSprite*)_touchedPanels->lastObject())){
               _touchedPanels->push(panel, _player);
           }
           // 既に、登録されたパネルのうえに来た時は、そこまで_touchedPanelsをpopしていく
           _touchedPanels->popTo(panel, _player);
        }
    }
}

//消えたパネルを取得する。
CCArray* Field::getRemovedPanels(){
    return _removedPanels;
}

void Field::setRemoved(){
    _touchedPanels->setRemoved(_player);
}

//消えたパネルの座標をセットする。
void Field::setRemovedPanel(CCPoint* point){
    _removedPanels->addObject(point);
}

PanelSprite* Field::createPanel(int indexX, int indexY){
    CCString* panelName = (CCString*) _panelNames->objectAtIndex(rand()%5);
    PanelSprite* pSprite = this->createPanelSprite(panelName->getCString());
    float size = PANEL_SIZE * PANEL_SCALE;
    pSprite->setSize(size);
    pSprite->setContentSize(CCSize(size,size));
    pSprite->setScale(PANEL_SCALE);
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size/2 + size * indexX, 96 + size/2 + size * indexY) );
    pSprite->update();
    return pSprite;
}

PanelSprite* Field::createPanelSprite(std::string panelName){
    PanelSprite* pSprite;
    if(panelName == "skelton"){
        pSprite = Enemy::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "potion"){
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "sword"){
        pSprite = Sword::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "coin"){
        pSprite = Coin::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "shield"){
        pSprite = Shield::createWithSpriteFrameName(panelName.c_str());
    } else {
        pSprite = PanelSprite::createWithSpriteFrameName(panelName.c_str());
    }
    return pSprite;
}

//消えたパネルの上に追加する。
void Field::restockPanels(){
    CCArray* removedPanels = this->getRemovedPanels();
    
    CCPoint *removedPoint = NULL;
    CCObject* targetObject = NULL;
    
    CCDictionary* removedCount = CCDictionary::create();
    
    CCARRAY_FOREACH(removedPanels, targetObject){
        removedPoint = (CCPoint*) targetObject;
        int y = 6;
        CCInteger* count = (CCInteger*) removedCount->objectForKey(removedPoint->x);
        //既にその列が消えている場合は、追加する場所がn段上になる。
        if(count){
            y += count->getValue();
            removedCount->setObject(CCInteger::create(count->getValue()+1),removedPoint->x);
        //その列がまだ消えていない場合は、dictionaryに追加
        } else {
            removedCount->setObject(CCInteger::create(1),removedPoint->x);
        }
        
        PanelSprite* pSprite = this->createPanel(int(removedPoint->x / (PANEL_SIZE * PANEL_SCALE)), y);
        _panels->addObject(pSprite);
        this->_parentLayer->addChild(pSprite);
    }
}

//フラグがたっているパネルを全部消す
void Field::removePanels(){
    CCArray* removedIndexes = CCArray::create();
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //消えるパネルなら消す。
        if(panel->isRemoved()){
            panel->removeFromParentAndCleanup(true);
            this->setRemovedPanel(new CCPoint(panel->getPositionX(), panel->getPositionY()));
            removedIndexes->addObject(CCInteger::create(count));
        }
        count++;
    }
    
    
    int maxIndex = removedIndexes->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndexes->objectAtIndex(i);
        this->_panels->removeObjectAtIndex(index->getValue());
    }
}

void Field::showDirections(){
    _touchedPanels->showDirections();
}

//移動量をパネル達にセットする。
//消えたパネルよりも上にあるパネルを取得して、セットする。
void Field::setMoves(){
    if(_moveState){
        return;
    }
    CCArray* removedPanels = this->getRemovedPanels();
    CCPoint *removedPoint = NULL;
    CCObject* targetObject1 = NULL;
    
    PanelSprite* panel = NULL;
    CCObject* targetObject2 = NULL;

    CCARRAY_FOREACH(this->_panels, targetObject1){
        panel = (PanelSprite*) targetObject1;
        CCARRAY_FOREACH(removedPanels, targetObject2){
            removedPoint = (CCPoint*) targetObject2;

            if(removedPoint->x == panel->getPositionX() && removedPoint->y < panel->getPositionY()){
                _moveState = true;
                panel->setDeltaY(PANEL_SIZE * PANEL_SCALE);
            }
        }
    }
}

//パネルを移動させる。
void Field::movePanels(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel->move()){
            movingPanelsNum++;
        }
    }
    if(movingPanelsNum == 0){
        _moveState = false;
    }
}

void Field::updateAllPanels(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->update();
    }
}

//ターン終了
void Field::onTurnEnd(){
    _touchedPanels->removeAllObjects();
    _removedPanels->removeAllObjects();
}

void Field::closeUp(){
}

void Field::cleanUp(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(_panels,  targetObject){
        panel = (PanelSprite*) targetObject;
        panel->removeAllDirectionSprite();
    }
    
}

