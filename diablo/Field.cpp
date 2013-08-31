//
//  Field.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#include "Field.h"
#include "PanelSprite.h"

Field::Field(CCLayer* parentLayer){
    this->_parentLayer = parentLayer;
    
    this->_panelNames = CCArray::create();
    this->_panelNames->retain();

//    CCArray *_panelNames = new CCArray();
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

CCArray* Field::getPanels(){
    return _panels;
}

void Field::onTouchStart(CCTouch* touch){
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //if(panel && panel->getTouchRect().containsPoint(tap)){
        if(panel && panel->boundingBox().containsPoint(tap)){
            panel->setTouched();
        }
    }
}

void Field::onTouchEnd(CCTouch* touch){
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->setUnTouched();
    }
}

void Field::onTouchMove(CCTouch* touch){
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
            panel->setTouched();
            panel->setRemoved();
        }
    }
}

//消えたパネルを取得する。
CCArray* Field::getRemovedPanels(){
    return _removedPanels;
}

//消えたパネルの座標をセットする。
void Field::setRemovedPanel(CCPoint* point){
    _removedPanels->addObject(point);
}

PanelSprite* Field::createPanel(int indexX, int indexY){
    CCString* panelName = (CCString*) _panelNames->objectAtIndex(rand()%5);
    PanelSprite* pSprite = PanelSprite::createWithSpriteFrameName(panelName->getCString());
    pSprite->setScale(PANEL_SCALE);
    float size = PANEL_SIZE * PANEL_SCALE;
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(32 + size * indexX, 128 + size * indexY) );
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


//ターン終了
void Field::onTurnEnd(){
    _removedPanels->removeAllObjects();
}

void Field::closeUp(){
}

