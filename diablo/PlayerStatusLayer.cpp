//
//  PlayerStatusLayer.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#include "PlayerStatusLayer.h"

CCScene* PlayerStatusLayer::scene(){
    PlayerStatusLayer *layer = (PlayerStatusLayer*) PlayerStatusLayer::layer();
    return layer->getScene();
}

PlayerStatusLayer* PlayerStatusLayer::layer(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PlayerStatusLayer *layer = (PlayerStatusLayer*) PlayerStatusLayer::create();
    layer->_player = Player::getPlayerMock();
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

PlayerStatusLayer* PlayerStatusLayer::layerWithPlayer(Player* player){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PlayerStatusLayer *layer = (PlayerStatusLayer*) PlayerStatusLayer::create();
    layer->_player = player;
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

void PlayerStatusLayer::setScene(CCScene* scene) {
    this->_scene = scene;
}

CCScene* PlayerStatusLayer::getScene(){
    return this->_scene;
}

bool PlayerStatusLayer::init(){
    CCLog("PlayerStatusLayer init");
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
    this->schedule(schedule_selector(PlayerStatusLayer::update));
    return true;
}

void PlayerStatusLayer::addWindowObjects(){
    CCLayerColor *background = CCLayerColor::create(ccc4(250, 0 , 250, 255));
    background->setContentSize(CCSizeMake(264, 344));
    background->setAnchorPoint(ccp(0,0));
    background->setPosition(ccp(28,108));
    this->addChild(background);
    
    CCLayerColor *layer = CCLayerColor::create(ccc4(250, 250, 250, 200));
    layer->setContentSize(CCSizeMake(260, 340));
    layer->setAnchorPoint(ccp(0,0));
    layer->setPosition(ccp(30,110));
    this->addChild(layer);
    

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Status", "arial", 17);

    pLabel->setColor(ccc3(0,0,0));
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(layer->getContentSize().width / 2, layer->getContentSize().height - 10) );

    // add the label as a child to this layer
    layer->addChild(pLabel, 1);
    _lineNum = 0;
    
    this->addStatusObject("base damage", _player->getBaseDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("sword damage", _player->getSwordDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("shield hp", _player->getShieldMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("shield refill", _player->getShieldRefill(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("hp", _player->getMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("potion recover", _player->getPotionRecover(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("coin addition", _player->getCoinAddition(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("strength", _player->getStrength(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("defense", _player->getDefense(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("dexterity", _player->getDexterity(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    this->addStatusObject("vitality", _player->getVitality(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    CCSprite* okOff = CCSprite::createWithSpriteFrameName("ok.png");
    okOff->setColor(ccc3(102,102,102));
    pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(PlayerStatusLayer::close));
    pOkButton->setAnchorPoint(ccp(0,0));
    pOkButton->setPosition(ccp(222, 114));
    
    CCMenu* pMenu = CCMenu::create(pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
}

void PlayerStatusLayer::addStatusObject(std::string name, int status, CCPoint position, CCNode* node){
    CCLOG("lineNum:%d", _lineNum);
    CCLabelTTF* pLabel = CCLabelTTF::create(name.c_str(), "arial", 10);
    pLabel->setColor(ccc3(0,0,0));
    pLabel->setAnchorPoint(ccp(0, 0));
    pLabel->setPosition(ccp(10, position.y - 15 * (_lineNum)));
    node->addChild(pLabel);
    
    CCLabelTTF* pStatus = CCLabelTTF::create(CCString::createWithFormat(": %d", status)->getCString(), "arial", 10);
    pStatus->setColor(ccc3(0,0,0));
    pStatus->setAnchorPoint(ccp(0,0));
    pStatus->setPosition(ccp(position.x + 100, position.y - 15 * (_lineNum)));
    node->addChild(pStatus);
    _lineNum++;
}


void PlayerStatusLayer::close(){
    this->removeFromParentAndCleanup(true);
}

bool PlayerStatusLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    return true;
}

void PlayerStatusLayer::update(){
}