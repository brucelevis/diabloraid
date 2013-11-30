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
    layer->player = new Player();
    layer->belongings = layer->player->getBelongings();
    
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
    layer->player = new Player();
    layer->belongings = layer->player->getBelongings();
    
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

DetailLayer* DetailLayer::layerWithUserItemAndPlayer(UserItem *userItem, Player *player){
    
       // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->userItem = userItem;
    layer->player = player;
    layer->belongings = player->getBelongings();
    
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
            this->windowObjects = UsableDetail::createWithUserItemAndPlayer(this->userItem, this->player);
            break;
        default:
            this->windowObjects = EquipmentDetail::createWithUserItemAndBelongings(this->userItem, this->belongings);
            break;
    }
    this->windowObjects->setParentLayer(this);
    
    //this->addWindowObjects();
    this->windowObjects->addWindowObjects();
    this->addChild((CCNode*) this->windowObjects);
}

void DetailLayer::addCommonComponents(){
    
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

void DetailLayer::closeParentLayer(){
    if(this->_parentLayer){
        this->_parentLayer->removeFromParentAndCleanup(true);
    }
}

void DetailLayer::setParentLayer(cocos2d::CCLayer *layer){
    this->_parentLayer = layer;
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
