//
//  DetailLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#include "DetailLayer.h"
CCScene* DetailLayer::scene(){
    DetailLayer *layer = (DetailLayer*) DetailLayer::layer();
    return layer->getScene();
}

DetailLayer* DetailLayer::layer(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->userItem = UserItem::getMock(2);
    layer->belongings = new Belongings();
    
    // add layer as a child to scene
    scene->addChild(layer);
    layer->setDetail();
    layer->addCommonComponents();
    
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}



DetailLayer* DetailLayer::layerWithUserItem(UserItem *userItem){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->userItem = userItem;
    layer->belongings = new Belongings();
    
    layer->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(layer->userItem, layer->belongings);
    //layer->addWindowObjects();
    layer->windowObjects->addWindowObjects();
    layer->addChild((CCNode*) layer->windowObjects);
    
    // add layer as a child to scene
    scene->addChild(layer);
    layer->setDetail();
    layer->addCommonComponents();
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

DetailLayer* DetailLayer::layerWithUserItemAndBelongings(UserItem *userItem, Belongings *belongings){
    
       // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->userItem = userItem;
    layer->belongings = belongings;
    
    layer->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(layer->userItem, layer->belongings);
    //layer->addWindowObjects();
    layer->windowObjects->addWindowObjects();
    layer->addChild((CCNode*)layer->windowObjects);
    
    // add layer as a child to scene
    scene->addChild(layer);
    layer->setDetail();
    layer->addCommonComponents();
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

void DetailLayer::setDetail(){
    switch(this->userItem->getType()){
        case EQUIPMENT:
            this->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(this->userItem, this->belongings);
            break;
        case USABLE:
            //this->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(this->userItem, this->belongings);
                this->windowObjects = UsableDetail::createWithUserItem(this->userItem);
            break;
        default:
                this->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(this->userItem, this->belongings);
            break;
    }
    
    //this->addWindowObjects();
    this->windowObjects->addWindowObjects();
    this->addChild((CCNode*) this->windowObjects);
}

void DetailLayer::addCommonComponents(){
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    CCSprite* okOff = CCSprite::createWithSpriteFrameName("ok.png");
    okOff->setColor(ccc3(102,102,102));
    this->pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(DetailLayer::close));
    this->pOkButton->setAnchorPoint(ccp(0,0));
    this->pOkButton->setPosition(ccp(222, 114));
    
    CCMenu* pMenu = CCMenu::create(this->pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
}

void DetailLayer::setScene(CCScene* scene) {
    this->_scene = scene;
}

CCScene* DetailLayer::getScene(){
    return this->_scene;
}

bool DetailLayer::init(){
    CCLog("DetailLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchPriority(kCCMenuHandlerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
    
    this->schedule(schedule_selector(DetailLayer::update));
    return true;
}

void DetailLayer::close(){
    this->removeFromParentAndCleanup(true);
}

void DetailLayer::addWindowObjects(){
    switch(userItem->getType()){
        case EQUIPMENT:
            break;
        case USABLE:
            break;
    }
}

bool DetailLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    return true;
}

void DetailLayer::update(){
    if(this->windowObjects){
        this->windowObjects->update();
    }
}
