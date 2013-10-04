//
//  BagListLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#include "BagListLayer.h"

CCScene* BagListLayer::scene(){
    BagListLayer *layer = (BagListLayer*) BagListLayer::layer();
    
    return layer->getScene();
}

BagListLayer* BagListLayer::layer(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BagListLayer *layer = (BagListLayer*) BagListLayer::create();
    layer->equipmentList = EquipmentList::getAll();
    layer->equipmentList->retain();
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

BagListLayer* BagListLayer::layerWithEquipmentList(EquipmentList* equipmentList){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BagListLayer *layer = (BagListLayer*) BagListLayer::create();
    layer->equipmentList = equipmentList;
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

bool BagListLayer::init(){
    CCLog("BagListLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
    this->setTouchPriority(kCCMenuHandlerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    this->schedule(schedule_selector(BagListLayer::update));
    return true;
}

void BagListLayer::setScene(CCScene* scene) {
    this->_scene = scene;
}

CCScene* BagListLayer::getScene(){
    return this->_scene;
}

void BagListLayer::addWindowObjects(){
    
    tableView = CCTableView::create(this, CCSizeMake(280, 340));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setDelegate(this);
    tableView->setAnchorPoint(ccp(0,0));
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(20, 100));
    tableView->setTouchPriority(kCCMenuHandlerPriority);
    this->addChild(tableView, 2);
    //CCLOG("tableView: touchPriority: %d", tableView->getTouchPriority());
    tableView->reloadData();
    
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    CCSprite* okOff = CCSprite::createWithSpriteFrameName("ok.png");
    okOff->setColor(ccc3(102,102,102));
    pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(BagListLayer::close));
    
    pOkButton->setAnchorPoint(ccp(0,0));
    pOkButton->setPosition(ccp(232, 64));
    
    CCMenu* pMenu = CCMenu::create(pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu);
}

void BagListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
    //LevelUpLayer *levelUpLayer = LevelUpLayer::layerWithAttributes(_player->getAttributes());
    if(equipmentList->count() < (cell->getIdx()+1)){
        return;
    }
    DetailLayer *detail = DetailLayer::layerWithEquipment((Equipment*) equipmentList->objectAtIndex(cell->getIdx()));
    this->addChild(detail->getScene(), 3);
}

CCSize BagListLayer::cellSizeForTable(CCTableView* table){
    return CCSizeMake(280, CELL_HEIGHT-2);
}

CCTableViewCell* BagListLayer::tableCellAtIndex(CCTableView* table, unsigned int idx){
    std::string name;
    if(equipmentList->count() >= (idx + 1)){
        Equipment *equipment =(Equipment*) equipmentList->objectAtIndex(idx);
        if(equipment->isEquipped()){
            name = equipment->getName() + "(E)";
        } else {
            name = equipment->getName();
        }
    } else {
        name = "空";
    }
    
    CCTableViewCell* cell = table->dequeueCell();
    if(!cell){
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCLayerColor *layer = CCLayerColor::create(ccc4(250, 250, 250, 200));
        layer->setContentSize(CCSizeMake(280, CELL_HEIGHT));
        layer->setAnchorPoint(ccp(0,0));
        layer->setPosition(ccp(0,0));
        layer->setTag(111);
        cell->addChild(layer, 2);
        
        CCLabelTTF* label = CCLabelTTF::create(name.c_str(), "Hiragino Kaku Gothic ProN", 16);
        label->setAnchorPoint(ccp(0, 0));
        label->setPosition(ccp(50, 28));
        label->setTag(112);
        label->setHorizontalAlignment(kCCTextAlignmentLeft);
        cell->addChild(label, 2);
        
        label->setColor(ccc3(0, 0, 0));
    }else{
        CCLabelTTF *label = (CCLabelTTF*) cell->getChildByTag(112);
        label->setString(name.c_str());
    }
    return cell;
}

unsigned int BagListLayer::numberOfCellsInTableView(CCTableView* table){
    return MAX(equipmentList->count(),6);
}

bool BagListLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    CCLOG("ccTouchBegan");
    return true;
}

int BagListLayer::getTableViewHeight(){
    int count = equipmentList->count();
    int height = MIN(count * CELL_HEIGHT, 340);
    return height;
}

void BagListLayer::close(){
    CCLOG("BagListLayer close");
    equipmentList->reload();
    this->removeFromParentAndCleanup(true);
}

void BagListLayer::update(){
    tableView->reloadData();
}

