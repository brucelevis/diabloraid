//
//  Field.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.

//

#include "Field.h"
#include "PanelSprite.h"
#include "EnemyMaster.h"
#include <math.h>

Field::Field(Player* player, Camera* camera, Floor* floor, FloorFieldModel* floorFieldModel){
    this->_player = player;
    this->_floor = floor;
    this->_connectPanel = NULL; //初期化
    this->_touchedPanels = (TouchedPanels*) TouchedPanels::create();
    this->_touchedPanels->retain();
    this->createInitialField(floorFieldModel, camera);
}

Field::~Field(void){
}


void Field::createInitialField(FloorFieldModel* floorFieldModel, Camera* camera){
    _panels = (FieldPanels*) FieldPanels::createWithFieldModel(floorFieldModel->getByIndex(0, 0), camera);// とりあえず、0,0をロードする。
    _panels->initialize((CCNode*) this, _floor);
    _panels->retain();
}

void Field::removeAllPanels(){
    this->_panels->removeAllPanels();
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
    if(this->_panels->isMoving()){
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
    if(this->_panels->isMoving()){
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

PanelSprite* Field::getConnectPanel(){
    return _connectPanel;
}

void Field::setRemoved(){
    _touchedPanels->setRemoved(_player);
}

void Field::initialize(){
    _touchedPanels->initialize();
}


//消えたパネルの上に追加する。
void Field::restockPanels(){
    _panels->restockPanel((CCNode*) this, _floor);
}

//フラグがたっているパネルを全部消す
void Field::removePanels(){
    _panels->removePanels();
}

void Field::showDirections(){
    _touchedPanels->showDirections();
}

//移動量をパネル達にセットする。
//消えたパネルよりも上にあるパネルを取得して、セットする。
void Field::setMoves(){
    _panels->setMoves();
}

//パネルを移動させる。
void Field::movePanels(){
    _panels->movePanels();
}

void Field::update(){
    this->movePanels();
    this->cleanUp();
    this->showDirections();
    _panels->update();
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
    this->_panels->refresh();
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


