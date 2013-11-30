//
//  BagLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#include "BagLayer.h"

CCScene* BagLayer::scene(){
    BagLayer *layer = (BagLayer*) BagLayer::layer();
    
    return layer->getScene();
}

BagLayer* BagLayer::layer(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BagLayer *layer = (BagLayer*) BagLayer::create();
    layer->userItem = UserItems::getAll();
    layer->userItem->retain();
    //layer->equipmentList = EquipmentList::getAll();
    //layer->equipmentList->retain();
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

BagLayer* BagLayer::layerWithUserItemsAndPlayer(UserItems* userItems, Player* player){
    //'scene' is an autorelease object
    CCScene *scene = CCScene::create();
  
    //'layer' is an autorelease object
    BagLayer *layer = (BagLayer*) BagLayer::create();
    layer->userItem = userItems;
    layer->player = player;
    layer->addWindowObjects();
   
    //add layer as a child to scene
    scene->addChild(layer);
  
    //return the scene
    layer->setScene(scene);
  
    return layer;
}

bool BagLayer::init(){
    CCLog("BagLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
    this->setTouchPriority(kCCMenuHandlerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    this->schedule(schedule_selector(BagLayer::update));
    return true;
}

void BagLayer::setScene(CCScene* scene) {
    this->_scene = scene;
}

CCScene* BagLayer::getScene(){
    return this->_scene;
}

void BagLayer::addWindowObjects(){
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
    CCMenuItemSprite::create(ok, okOff, this, menu_selector(BagLayer::close));
    
    pOkButton->setAnchorPoint(ccp(0,0));
    pOkButton->setPosition(ccp(232, 64));
    
    CCMenu* pMenu = CCMenu::create(pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu);
}

void BagLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
    if(userItem->count() < (cell->getIdx()+1)){
        return;
    }
    DetailLayer *detail = DetailLayer::layerWithUserItemAndPlayer((UserItem*) userItem->objectAtIndex(cell->getIdx()),this->player);
    detail->setParentLayer((CCLayer*) this);
    this->addChild(detail->getScene(), 3);
}

CCSize BagLayer::cellSizeForTable(CCTableView* table){
    return CCSizeMake(280, CELL_HEIGHT-2);
}

CCTableViewCell* BagLayer::tableCellAtIndex(CCTableView* table, unsigned int idx){
    std::string name;
    if(userItem->count() >= (idx + 1)){
        UserItem* item = (UserItem*) userItem->objectAtIndex(idx);
        if(item->isEquipped()){
            name = item->getName() + "(E)";
        } else {
            name = item->getName();
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

unsigned int BagLayer::numberOfCellsInTableView(CCTableView* table){
    return MAX(userItem->count(),6);
}

bool BagLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    CCLOG("ccTouchBegan");
    return true;
}

int BagLayer::getTableViewHeight(){
    int count = userItem->count();
    int height = MIN(count * CELL_HEIGHT, 340);
    return height;
}

void BagLayer::close(){
    CCLOG("BagLayer close");
    this->removeFromParentAndCleanup(true);
}

void BagLayer::update(){
    tableView->reloadData();
}

