//
//  BagListLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#include "BagListLayer.h"

CCScene* BagListLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BagListLayer *layer = (BagListLayer*) BagListLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BagListLayer::init(){
    CCLog("BagListLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //this->setTouchPriority(kBagListLayerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    equipmentList = Equipment::getAll();
    equipmentList->retain();
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(280, 340));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setDelegate(this);
    tableView->setAnchorPoint(ccp(0,0));
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(20, 100));
    this->addChild(tableView, 1);
    tableView->reloadData();
    
    this->schedule(schedule_selector(BagListLayer::update));
    return true;
}

void BagListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
    CCLOG("cell touch idx: %i", cell->getIdx());
}

CCSize BagListLayer::cellSizeForTable(CCTableView* table){
    return CCSizeMake(280, CELL_HEIGHT-2);
}

CCTableViewCell* BagListLayer::tableCellAtIndex(CCTableView* table, unsigned int idx){
    std::string name;
    if(equipmentList->count() >= (idx + 1)){
        Equipment *equipment =(Equipment*) equipmentList->objectAtIndex(idx);
        name = equipment->getName();
    } else {
        name = "空";
    }
    
    CCTableViewCell* cell = table->dequeueCell();
    if(!cell){
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCLayerColor *layer = CCLayerColor::create(ccc4(250, 250, 250, 122 ));
        layer->setContentSize(CCSizeMake(280, CELL_HEIGHT));
        layer->setAnchorPoint(ccp(0,0));
        layer->setPosition(ccp(0,0));
        layer->setTag(111);
        cell->addChild(layer);
        
        CCLabelTTF* label = CCLabelTTF::create(name.c_str(), "Hiragino Kaku Gothic ProN", 16);
        label->setAnchorPoint(ccp(0, 0));
        label->setPosition(ccp(50, 28));
        label->setTag(112);
        label->setHorizontalAlignment(kCCTextAlignmentLeft);
        cell->addChild(label);
        
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
    return true;
}

int BagListLayer::getTableViewHeight(){
    int count = equipmentList->count();
    int height = MIN(count * CELL_HEIGHT, 340);
    return height;
}