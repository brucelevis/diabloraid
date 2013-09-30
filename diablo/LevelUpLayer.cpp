//
//  LevelUpLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/20.
//
//

#include "LevelUpLayer.h"


CCScene* LevelUpLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelUpLayer *layer = (LevelUpLayer*) LevelUpLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LevelUpLayer::init(){
    CCLog("LevelUpLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // create menu, it's an autorelease object
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
    
    CCSprite* base = CCSprite::createWithSpriteFrameName("dialog.png");
    base->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(base);
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    ok->setPosition(ccp(base->getContentSize().width - 60, base->getContentSize().height - 250));
    base->addChild(ok);
    
    CCLabelTTF* title = CCLabelTTF::create("Level Up!!!", "Thonburi", 20);
    title->setPosition(ccp(base->getContentSize().width/2, base->getContentSize().height - 40));
    base->addChild(title, 1);
    
    remainings = CCLabelTTF::create(CCString::createWithFormat("remain: %d", this->remain)->getCString(), "arial", 20);
    remainings->setPosition(ccp(80, 60));
    base->addChild(remainings);
    
    this->remain = 5;
    status = CCArray::create();
    status->retain();
    
    strength = StatusUpgrade::createStatusLine("Strength", 10, ccp(base->getContentSize().width, base->getContentSize().height - 80), this->remain);
    base->addChild(strength);
    status->addObject(strength);
    
    defense  = StatusUpgrade::createStatusLine("Defense", 5, ccp(base->getContentSize().width, base->getContentSize().height - 120), this->remain);
    base->addChild(defense);
    status->addObject(defense);
    
    dexterity  = StatusUpgrade::createStatusLine("Dexterity", 123, ccp(base->getContentSize().width, base->getContentSize().height - 160), this->remain);
    base->addChild(dexterity);
    status->addObject(dexterity);
    
    vitality  = StatusUpgrade::createStatusLine("Vitality", 84, ccp(base->getContentSize().width, base->getContentSize().height - 200), this->remain);
    base->addChild(vitality);
    status->addObject(vitality);
    
    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(LevelUpLayer::update));
    return true;
}

void LevelUpLayer::update(){
    StatusUpgrade* upgrader;
    CCObject* targetObject;
    
    int currentTotal = 0;
    CCARRAY_FOREACH(this->status, targetObject){
        upgrader = (StatusUpgrade*) targetObject;
        currentTotal += upgrader->getCurrentAddition();
    }
    
    CCARRAY_FOREACH(this->status, targetObject){
        upgrader = (StatusUpgrade*) targetObject;
        upgrader->setRemain(this->remain - currentTotal);
    }
    
    this->remainings->setString(CCString::createWithFormat("remain: %d", this->remain - currentTotal)->getCString());
}