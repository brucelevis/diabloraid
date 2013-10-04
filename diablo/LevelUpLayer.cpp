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

LevelUpLayer* LevelUpLayer::layer(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelUpLayer *layer = (LevelUpLayer*) LevelUpLayer::create();
    layer->_player = Player::getPlayerMock();
    layer->addWidowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    
    return layer;
}

LevelUpLayer* LevelUpLayer::layerWithAttributes(Attributes* attributes){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelUpLayer *layer = (LevelUpLayer*) LevelUpLayer::create();
    layer->_player = Player::getPlayerMock();
    layer->_player->setAttributes(attributes);
    layer->addWidowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    return layer;
}

LevelUpLayer* LevelUpLayer::layerWithPlayer(Player* player){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelUpLayer *layer = (LevelUpLayer*) LevelUpLayer::create();
    layer->_player = player;
    layer->addWidowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    return layer;
}

void LevelUpLayer::setScene(CCScene* scene) {
    this->_scene = scene;
}

CCScene* LevelUpLayer::getScene(){
    return this->_scene;
}

void LevelUpLayer::setCallback(Events *events, cocos2d::CCLayer *layer){
    this->_events = events;
    this->_parentLayer = layer;
}


bool LevelUpLayer::init(){
    CCLog("LevelUpLayer init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //this->setTouchPriority(kLevelUpLayerPriority);
    this->setTouchPriority(kCCMenuHandlerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    this->schedule(schedule_selector(LevelUpLayer::update));
    return true;
}

void LevelUpLayer::addWidowObjects(){
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // create menu, it's an autorelease object
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* base = CCSprite::createWithSpriteFrameName("dialog.png");
    base->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(base);
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    CCSprite* okOff = CCSprite::createWithSpriteFrameName("ok.png");
    okOff->setColor(ccc3(102,102,102));
    pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(LevelUpLayer::close));
    
    pOkButton->setPosition(ccp(base->getContentSize().width - 60, base->getContentSize().height - 250));
    pOkButton->setVisible(false);
    
    CCMenu* pMenu = CCMenu::create(pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    
    base->addChild(pMenu);
    
    CCLabelTTF* title = CCLabelTTF::create("Level Up!!!", "Thonburi", 20);
    title->setPosition(ccp(base->getContentSize().width/2, base->getContentSize().height - 40));
    title->setColor(ccc3(0,0,0));
    base->addChild(title, 1);
    
    remainings = CCLabelTTF::create(CCString::createWithFormat("remain: %d", this->remain)->getCString(), "arial", 20);
    remainings->setPosition(ccp(80, 60));
    remainings->setColor(ccc3(0,0,0));
    base->addChild(remainings);
    
    this->remain = 3;
    status = CCArray::create();
    status->retain();
    
    strength = StatusUpgrade::createStatusLine("Strength", _player->getStrength(), ccp(base->getContentSize().width, base->getContentSize().height - 80), this->remain);
    base->addChild(strength);
    status->addObject(strength);
    
    defense  = StatusUpgrade::createStatusLine("Defense", _player->getDefense(), ccp(base->getContentSize().width, base->getContentSize().height - 120), this->remain);
    base->addChild(defense);
    status->addObject(defense);
    
    dexterity  = StatusUpgrade::createStatusLine("Dexterity", _player->getDexterity(), ccp(base->getContentSize().width, base->getContentSize().height - 160), this->remain);
    base->addChild(dexterity);
    status->addObject(dexterity);
    
    vitality  = StatusUpgrade::createStatusLine("Vitality", _player->getVitality(), ccp(base->getContentSize().width, base->getContentSize().height - 200), this->remain);
    base->addChild(vitality);
    status->addObject(vitality);
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
    if((this->remain - currentTotal) == 0 ){
        pOkButton->setVisible(true);
    } else {
        pOkButton->setVisible(false);
    }
}

bool LevelUpLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    return true;
}

void LevelUpLayer::close(){
    this->removeFromParentAndCleanup(true);
    this->_events->setHandling(false);
    this->_player->getAttributes()->addStrength(strength->getCurrentAddition());
    this->_player->getAttributes()->addDefense(defense->getCurrentAddition());
    this->_player->getAttributes()->addDexterity(dexterity->getCurrentAddition());
    this->_player->getAttributes()->addVitality(vitality->getCurrentAddition());
    this->_player->recoverAllHp();
    this->_events->handle(this->_parentLayer);
}