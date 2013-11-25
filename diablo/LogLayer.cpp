//
//  LogLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/25.
//
//

#include "LogLayer.h"

CCScene* LogLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LogLayer *layer = (LogLayer*) LogLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

LogLayer* LogLayer::layerWithText(std::string text){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LogLayer *layer = (LogLayer*) LogLayer::create();
    layer->_scene = scene;
    
    CCLayerColor *background = CCLayerColor::create(ccc4(250, 255 , 250, 122));
    background->setContentSize(CCSizeMake(360, 40));
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(0, 20));
    
    CCLabelTTF* pLabel = CCLabelTTF::create(text.c_str(), "Thonburi", 17);
    pLabel->setColor(ccc3(0, 0, 0));
    pLabel->setAnchorPoint(ccp(0, 0.5));
    pLabel->setPosition(ccp(10,  background->getContentSize().height / 2) );
    background->addChild(pLabel);
    
    CCMoveTo* move = CCMoveTo::create(2.0f,ccp(0, size.height / 2));
    CCFadeOut* fo  = CCFadeOut::create(2.0f);
    CCSpawn* spawn = CCSpawn::createWithTwoActions(move, fo);
    
    CCCallFunc *func = CCCallFunc::create(layer, callfunc_selector(LogLayer::close));
    CCCallFunc* funcNext = CCCallFunc::create(layer, callfunc_selector(LogLayer::next));
    
    background->runAction(CCSequence::create(spawn, func, NULL));
    background->runAction(CCSequence::create(CCDelayTime::create(0.5f), funcNext, NULL));
    
    layer->addChild(background);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return layer;
    
}

void LogLayer::setCallback(Events *events, cocos2d::CCLayer *layer){
    this->_events = events;
    this->_parentLayer = layer;
}

LogLayer* LogLayer::layer(){
    return LogLayer::layerWithText("薬草を手に入れた");
}

bool LogLayer::init(){
    CCLog("LogLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->schedule(schedule_selector(LogLayer::update));
    return true;
}

CCScene* LogLayer::getScene(){
    return this->_scene;
}


void LogLayer::close(){
    this->removeFromParentAndCleanup(true);
}

void LogLayer::next(){
    this->_events->setHandling(false);
    this->_events->handle(this->_parentLayer);
}