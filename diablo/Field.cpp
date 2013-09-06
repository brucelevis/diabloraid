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
#include <math.h>

Field::Field(CCLayer* parentLayer){
    this->_parentLayer = parentLayer;
    
    this->_panelNames = CCArray::create();
    this->_panelNames->retain();
    this->_touchedPanels = CCArray::create();
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

void Field::pushTouchedPanels(PanelSprite* panel){
    // 最初の一回だけ登録
    if(_touchedPanels->containsObject((CCObject*) panel)){
        return;
    }
    
    _touchedPanels->addObject(panel);
}

void Field::popTouchedPanels(PanelSprite *panel){
    if(_touchedPanels->lastObject() == panel){
        return;
    }
    if(!_touchedPanels->containsObject(panel)){
        return;
    }
    
    int index = _touchedPanels->indexOfObject((CCObject*) panel);
    
    int lastCount = _touchedPanels->count() - 1;
    for(int i = lastCount; i > index; i--){
        _touchedPanels->removeObjectAtIndex(i);
    }
    _lastPanel = (PanelSprite*) _touchedPanels->objectAtIndex(index);
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
            _lastPanel = panel;
            this->pushTouchedPanels(panel);
        }
    }
    
    CCARRAY_FOREACH(this->_panels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        if(panel && panel->isSamePanel(_touchedPanelName)){
            panel->switchOn();
        } else {
            panel->switchOff();
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
    this->setRemoved();
    _touchedPanelName = "";//初期化
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
           if(panel->isSamePanel(_touchedPanelName) && panel->isNextPanel(_lastPanel)){
                _lastPanel = panel;
                this->pushTouchedPanels(panel);
           }
           // 既に、登録されたパネルのうえに来た時は、そこまで_touchedPanelsをpopしていく
           this->popTouchedPanels(panel);
        }
    }
}

//消えたパネルを取得する。
CCArray* Field::getRemovedPanels(){
    return _removedPanels;
}

void Field::setRemoved(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(_touchedPanels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->setRemoved();
    }
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
    pSprite->setUnTouched();
    return pSprite;
}

PanelSprite* Field::createPanelSprite(std::string panelName){
    PanelSprite* pSprite;
    if(panelName == "skelton"){
        pSprite = Enemy::createWithSpriteFrameName(panelName.c_str());
    } else if(panelName == "potion"){
        pSprite = Potion::createWithSpriteFrameName(panelName.c_str());
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
    //順に消えるパネルを取得して、それに合わせて、CCSpriteを生成して、表示する。
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    PanelSprite* _beforePanel;
    PanelSprite* _currentPanel;
    PanelSprite* _nextPanel;
    
    int lastCount = _touchedPanels->count() - 1;
    CCARRAY_FOREACH(_touchedPanels, targetObject){
        panel = (PanelSprite*) targetObject;
        
        if(count == 0){
            //スタート地点の時は何もしない。
            _beforePanel = panel;
        } else if(count == 1){
            _currentPanel = panel;
            //スタート地点に画像を出す。
            //スタート地点から今のパネルへの方向を得る。
            int direction = _beforePanel->getDirection(_currentPanel);
            _beforePanel->pushDirectionSprite(CCString::createWithFormat("5%d", direction)->intValue());
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int directionA = panel->getDirection(_beforePanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", directionA)->intValue());
            }
        } else if(count == 2){
            //2のとき
            _nextPanel = panel;
            //一個前の位置に方向を出す。
            int directionA = _currentPanel->getDirection(_beforePanel);
            int directionB = _currentPanel->getDirection(_nextPanel);
            if( directionA < directionB){
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionA, directionB )->intValue());
            } else {
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionB, directionA )->intValue());
            }
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int direction = panel->getDirection(_currentPanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", direction)->intValue());
            }
        } else {
            //2以上のとき
            _beforePanel = _currentPanel;
            _currentPanel = _nextPanel;
            _nextPanel = panel;
            int directionA = _currentPanel->getDirection(_beforePanel);
            int directionB = _currentPanel->getDirection(_nextPanel);
            if( directionA < directionB){
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionA, directionB )->intValue());
            } else {
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionB, directionA )->intValue());
            }
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int direction = panel->getDirection(_currentPanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", direction)->intValue());
            }
        }
        count++;
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

