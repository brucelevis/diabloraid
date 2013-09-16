//
//  Field.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#include "Field.h"
#include "PanelSprite.h"
#include "EnemyMaster.h"
#include <math.h>

Field::Field(CCLayer* parentLayer, Player* player){
    this->_player = player;
    this->_parentLayer = parentLayer;
    this->_connectPanel = NULL; //初期化
    this->_touchedPanels = (TouchedPanels*) TouchedPanels::create();
    this->_touchedPanels->retain();
    
}

Field::~Field(void){
}


CCArray* Field::createInitialField(){
    _panels = (FieldPanels*) FieldPanels::create();
    _panels->initialize();
    _panels->retain();
    _removedPanels = CCArray::create();
    _removedPanels->retain();
    _floor = new Floor(1); //スタートは1から。　
    for(int i = 0; i <= 5; i++){
        for( int j = 0; j <= 5; j++){
            PanelSprite* pSprite = _panels->createPanel(_floor, i, j, PANEL_SIZE * PANEL_SCALE, PANEL_SCALE);
            // add the sprite as a child to this layer
            _panels->add(pSprite);
        }
    }
    
    return _panels;
}

void Field::removeAllPanels(){
    CCArray* removedIndexes = CCArray::create();
   
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //消えるパネルなら消す。
        panel->removeFromParentAndCleanup(true);
        this->setRemovedPanel(new CCPoint(panel->getPositionX(), panel->getPositionY()));
        removedIndexes->addObject(CCInteger::create(count));
        count++;
    }
    
    
    int maxIndex = removedIndexes->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndexes->objectAtIndex(i);
        this->_panels->remove(index->getValue());
    }
}

CCArray* Field::getEnemies(){
    CCArray* enemies = CCArray::create();
    
    PanelSprite* panel;
    CCObject* targetObject;
    CCARRAY_FOREACH(_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel->isEnemy()){
            enemies->addObject((CCObject*) panel);
        }
    }
    return enemies;
}

CCArray* Field::getPanels(){
    return _panels;
}

int Field::getTurn(){
    return _floor->getTurn();
}

int Field::getFloor(){
    return _floor->getFloor();
}

void Field::gotoNextFloor(){
    _floor->countupFloor(1);
}

TouchedPanels* Field::getWillBeRemovedPanel(){
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

PanelSprite* Field::getConnectPanel(){
    return _connectPanel;
}

void Field::setRemoved(){
    _touchedPanels->setRemoved(_player);
}

void Field::initialize(){
    _touchedPanels->initialize();
}

//消えたパネルの座標をセットする。
void Field::setRemovedPanel(CCPoint* point){
    _removedPanels->addObject(point);
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
        
        float size = PANEL_SIZE * PANEL_SCALE;
        PanelSprite* pSprite = _panels->createPanel(_floor, int(removedPoint->x / (PANEL_SIZE * PANEL_SCALE)), y, size, PANEL_SCALE);
        _panels->add(pSprite);
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
        this->_panels->remove(index->getValue());
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
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->update();
    }
}

//ターン終了
void Field::onTurnEnd(){
    _touchedPanels->removeAllObjects();
    CCLog("_touchedPanelsNum:%d", _touchedPanels->count());
    _removedPanels->removeAllObjects();
    this->updateAllPanels();
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

void Field::countUpTurn(){
    _floor->countupTurn(1); //ターンを進める。
}

