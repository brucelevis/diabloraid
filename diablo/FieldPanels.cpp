//
//  FieldPanels.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/15.
//
//

#include "FieldPanels.h"
FieldPanels::FieldPanels(FloorFieldModel* _floorFieldModel, Camera* camera){
    _removedPanels = CCArray::create();
    _removedPanels->retain();
    this->camera  = camera;
    this->_floorFieldModel = _floorFieldModel;
}

FieldPanels::~FieldPanels(){
}

void FieldPanels::add(PanelSprite* panel){
    this->addCount(panel);
    this->addObject((CCObject*) panel);
}

void FieldPanels::remove(int index){
    PanelSprite* panel = (PanelSprite*) this->objectAtIndex(index);
    this->decreaseCount(panel);
    this->removeObjectAtIndex(index);
}

void FieldPanels::initialize(CCNode* parentNode, Floor* floor){
    _panelCount = CCDictionary::create();
    _panelCount->retain();
   for(int i = 0; i <= 5; i++){
       for( int j = 0; j <= 5; j++){
            PanelSprite* pSprite = this->loadPanel(i, j);
            // add the sprite as a child to this layer
            this->add(pSprite);
            parentNode->addChild(pSprite);
       }
   }
}

void FieldPanels::restockPanel(CCNode* parentNode, Floor* floor){
    CCArray* removedPanels = this->getRemovedPanels();
    
    PanelSprite* removedPanel = NULL;
    CCObject* targetObject = NULL;
    
    CCDictionary* removedCount = CCDictionary::create();
    
    CCARRAY_FOREACH(removedPanels, targetObject){
        removedPanel = (PanelSprite*) targetObject;
        int y = 6;
        CCInteger* count = (CCInteger*) removedCount->objectForKey(removedPanel->getAbsolutePosition().x);
        //既にその列が消えている場合は、追加する場所がn段上になる。
        if(count){
            y += count->getValue();
            removedCount->setObject(CCInteger::create(count->getValue()+1),removedPanel->getAbsolutePosition().x);
        //その列がまだ消えていない場合は、dictionaryに追加
        } else {
            removedCount->setObject(CCInteger::create(1),removedPanel->getAbsolutePosition().x);
        }
        
        PanelSprite* pSprite = this->createPanel(floor, int(removedPanel->getAbsolutePosition().x / (PANEL_SIZE * PANEL_SCALE)), y);
        this->add(pSprite);
        parentNode->addChild(pSprite);
    }
}

void FieldPanels::removePanels(){
    CCArray* removedIndexes = CCArray::create();
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //消えるパネルなら消す。
        if(panel->isRemoved()){
            panel->removeFromParentAndCleanup(true);
            this->setRemovedPanel(panel);
            
            removedIndexes->addObject(CCInteger::create(count));
        }
        count++;
    }
    
    
    int maxIndex = removedIndexes->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndexes->objectAtIndex(i);
        this->remove(index->getValue());
    }
}

void FieldPanels::removeAllPanels(){
    CCArray* removedIndexes = CCArray::create();
   
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //消えるパネルなら消す。
        panel->removeFromParentAndCleanup(true);
        this->setRemovedPanel(panel);
        removedIndexes->addObject(CCInteger::create(count));
        count++;
    }
    
    
    int maxIndex = removedIndexes->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndexes->objectAtIndex(i);
        this->remove(index->getValue());
    }
}

void FieldPanels::setMoves(){
    if(_moveState){
       return;
    }
    CCArray* removedPanels = this->getRemovedPanels();
    PanelSprite* removedPanel = NULL;
    CCObject* targetObject1 = NULL;
    
    PanelSprite* panel = NULL;
    CCObject* targetObject2 = NULL;

    CCARRAY_FOREACH(this, targetObject1){
        panel = (PanelSprite*) targetObject1;
        CCARRAY_FOREACH(removedPanels, targetObject2){
            removedPanel = (PanelSprite*) targetObject2;

            if(removedPanel->getAbsolutePosition().x == panel->getAbsolutePosition().x && removedPanel->getAbsolutePosition().y < panel->getAbsolutePosition().y){
                _moveState = true;
                panel->setDeltaY(PANEL_SIZE * PANEL_SCALE);
            }
        }
    }
}

void FieldPanels::movePanels(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel->move()){
            movingPanelsNum++;
            _onMovingEndCalling = false;
        }
    }
    if(movingPanelsNum == 0){
        _moveState = false;
    }
}

bool FieldPanels::isMoving(){
    return _moveState;
}

CCArray* FieldPanels::createWithFloorFieldModel(FloorFieldModel *floorFieldModel, Camera* camera){
    CCArray* pArray = (CCArray*) new FieldPanels(floorFieldModel, camera);
  
    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

int FieldPanels::getCurrentPanelNum(PanelSprite* panel){
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        return count->getValue();
    } else {
        return 0;
    }
}

void FieldPanels::addCount(PanelSprite* panel){
    //パネルの名前ごとにカウントする。
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        count->getValue();
        _panelCount->setObject(CCInteger::create(count->getValue()+1), panel->getPanelName());
    } else {
        _panelCount->setObject(CCInteger::create(1), panel->getPanelName());
    }
}

void FieldPanels::decreaseCount(PanelSprite* panel){
    //パネルの名前ごとにカウントする。
    CCInteger* count = (CCInteger*) _panelCount->objectForKey(panel->getPanelName());
    if(count){
        count->getValue();
        _panelCount->setObject(CCInteger::create(count->getValue()-1), panel->getPanelName());
    } else {
        CCLog("assert impossible!!!");
    }
}

PanelSprite* FieldPanels::createPanel(Floor* floor, int indexX, int indexY){
    PanelSprite* pSprite = PanelSpriteFactory::createWithFloor(floor);
    
    if(!pSprite->canBeAdded(this->getCurrentPanelNum(pSprite))){
        pSprite->release();
        return this->createPanel(floor, indexX, indexY);
    }
    
    float size = PANEL_SIZE * PANEL_SCALE;
    float scale = PANEL_SCALE;
    pSprite->setCameraPos(camera->getPosition());
    pSprite->setSize(size);
    pSprite->setContentSize(CCSize(size,size));
    pSprite->setScale(scale);
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size/2 + size * indexX - camera->getPosition()->x, OFFSET_Y + size/2 + size * indexY - camera->getPosition()->y) );
    pSprite->setAbsolutePosition( ccp(size * indexX, size * indexY) );
    pSprite->update();
    return pSprite;
}

PanelSprite* FieldPanels::loadPanel(int indexX, int indexY){
    int id = _floorFieldModel->get(indexX, indexY);
    ModelManager* modelManager = ModelManager::getInstance();
    PanelDataManager* panelDataManager =(PanelDataManager*) modelManager->getModel("PanelData");
    PanelData* panelData =(PanelData*) panelDataManager->getByPrimaryKey(id);
    
    PanelSprite* pSprite = PanelSpriteFactory::createByPanelData(panelData);
    
    float size = PANEL_SIZE * PANEL_SCALE;
    float scale = PANEL_SCALE;
    pSprite->setCameraPos(camera->getPosition());
    pSprite->setSize(size);
    pSprite->setContentSize(CCSize(size,size));
    pSprite->setScale(scale);
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size/2 + size * indexX - camera->getPosition()->x, OFFSET_Y + size/2 + size * indexY - camera->getPosition()->y) );
    pSprite->setAbsolutePosition( ccp(size * indexX, size * indexY) );
    pSprite->update();
    return pSprite;
}

//消えたパネルを取得する。
CCArray* FieldPanels::getRemovedPanels(){
    return _removedPanels;
}

void FieldPanels::refresh(){
    _removedPanels->removeAllObjects();
}

//現在のパネル状況をmodelにアップデートする。
void FieldPanels::save(){
    CCLOG("save");
    PanelSprite* pSprite;
    CCObject* targetObject;
    float size = PANEL_SIZE * PANEL_SCALE;
    CCARRAY_FOREACH(this, targetObject){
        pSprite = (PanelSprite*) targetObject;
        CCPoint pos = pSprite->getAbsolutePosition();
        int x = (int) ((pos.x) / size);
        int y = (int) ((pos.y) / size );
        _floorFieldModel->set(x, y, pSprite->getId());
    }
}

//消えたパネルの座標をセットする。
void FieldPanels::setRemovedPanel(PanelSprite* panel){
    _removedPanels->addObject(panel);
}

void FieldPanels::update(){
   this->switchActiveState();
   this->adjustPosition();
   if(!this->isMoving() && !_onMovingEndCalling){
       //最初の一回だけ呼ぶ
       this->onMovingEnd();
       _onMovingEndCalling = true;
   }
}

void FieldPanels::adjustPosition(){
    PanelSprite* pSprite;
    CCObject* targetObject;
    CCARRAY_FOREACH(this, targetObject){
        pSprite = (PanelSprite*) targetObject;
        CCPoint absolutePos = pSprite->getAbsolutePosition();
        float size = PANEL_SIZE * PANEL_SCALE;
        pSprite->setPosition(ccp(size/2 + absolutePos.x - camera->getPosition()->x, OFFSET_Y + size/2 +absolutePos.y - camera->getPosition()->y));
    }
}

void FieldPanels::onMovingEnd(){
    this->save();
    this->camera->setMove(true);
}

void FieldPanels::switchActiveState(){
    PanelSprite* pSprite;
    CCObject* targetObject;
    CCARRAY_FOREACH(this, targetObject){
        pSprite = (PanelSprite*) targetObject;
        if(this->camera->intersectsRect(pSprite)){
            pSprite->setActiveState(true);
        } else {
            pSprite->setActiveState(false);
        }//cameraの中にあれば、visibleにする。
    }
}