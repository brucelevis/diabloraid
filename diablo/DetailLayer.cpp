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
    layer->_equipment = Equipment::getMock();
    layer->_belongings = new Belongings();
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

DetailLayer* DetailLayer::layerWithEquipment(Equipment *equipment){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->_equipment = equipment;
    layer->_belongings = new Belongings();
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
}

DetailLayer* DetailLayer::layerWithEquipmentAndBelongings(Equipment *equipment, Belongings *belongings){
    
       // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DetailLayer *layer = (DetailLayer*) DetailLayer::create();
    layer->_equipment = equipment;
    layer->_belongings = belongings;
    layer->addWindowObjects();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->setScene(scene);
    
    return layer;
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
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
    this->schedule(schedule_selector(DetailLayer::update));
    return true;
}

void DetailLayer::addWindowObjects(){
    CCLayerColor *background = CCLayerColor::create(ccc4(0, 250, 250, 255));
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
    CCLabelTTF* pLabel = CCLabelTTF::create("Item Detail", "arial", 17);

    pLabel->setColor(ccc3(0,0,0));
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(layer->getContentSize().width / 2, layer->getContentSize().height - 10) );

    // add the label as a child to this layer
    layer->addChild(pLabel, 1);
    _lineNum = 0;
    
    this->addStatusObject("name", CCString::createWithFormat("%s", _equipment->getName().c_str()), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    
    Equipment* _current = _belongings->get(_equipment->getCategory());
    baseDamageLabel = this->addStatusObject("base damage", _equipment->getBaseDamage(), _current->getBaseDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    swordDamageLabel = this->addStatusObject("sword damage", _equipment->getSwordDamage(), _current->getSwordDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    shieldHpLabel = this->addStatusObject("shield hp", _equipment->getShieldMaxHp(), _current->getShieldMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    shieldRefillLabel = this->addStatusObject("shield refill", _equipment->getShieldRefill(), _current->getShieldRefill(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    maxHpLabel = this->addStatusObject("hp", _equipment->getMaxHp(), _current->getMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    potionRecoverLabel = this->addStatusObject("potion recover", _equipment->getPotionRecover(), _current->getPotionRecover(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    coinAdditionLabel = this->addStatusObject("coin addition", _equipment->getCoinAddition(), _current->getCoinAddition(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    strengthLabel = this->addStatusObject("strength", _equipment->getStrength(), _current->getStrength(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    defenseLabel = this->addStatusObject("defense", _equipment->getDefense(), _current->getDefense(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    dexterityLabel = this->addStatusObject("dexterity", _equipment->getDexterity(), _current->getDexterity(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    vitalityLabel = this->addStatusObject("vitality", _equipment->getVitality(), _current->getVitality(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    
    CCLabelTTF* equipLabel = CCLabelTTF::create("eqiup","arial", 10);
    equipLabel->setColor(ccc3(0,0,0));
    equipLabel->setAnchorPoint(ccp(0, 0));
    equipLabel->setPosition(ccp(10, layer->getContentSize().height - 35 - 15 * (_lineNum)));
    layer->addChild(equipLabel);
    
    CCString* equipStatus;
    if (_equipment->isEquipped()){
        equipStatus = CCString::create(": on");
    } else {
        equipStatus = CCString::create(": off");
    }
    equipStatusLabel = CCLabelTTF::create(equipStatus->getCString(), "arial", 10);
    equipStatusLabel->setColor(ccc3(0,0,0));
    equipStatusLabel->setAnchorPoint(ccp(0,0));
    equipStatusLabel->setPosition(ccp(100, layer->getContentSize().height -35 - 15 * (_lineNum)));
    layer->addChild(equipStatusLabel);
    
    CCSprite* ok = CCSprite::createWithSpriteFrameName("ok.png");
    CCSprite* okOff = CCSprite::createWithSpriteFrameName("ok.png");
    okOff->setColor(ccc3(102,102,102));
    pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(DetailLayer::close));
    pOkButton->setAnchorPoint(ccp(0,0));
    pOkButton->setPosition(ccp(222, 114));
    
    CCSprite* equip = CCSprite::createWithSpriteFrameName("equip.png");
    CCSprite* equipOff = CCSprite::createWithSpriteFrameName("equip.png");
    equipOff->setColor(ccc3(102,102,102));
    pEquipButton =
        CCMenuItemSprite::create(equip, equipOff, this, menu_selector(DetailLayer::equip));
    pEquipButton->setAnchorPoint(ccp(0,0));
    pEquipButton->setPosition(ccp(222 - 68, 114));
    pEquipButton->setVisible(!this->_equipment->isEquipped());
    
    CCSprite* remove = CCSprite::createWithSpriteFrameName("remove.png");
    CCSprite* removeOff = CCSprite::createWithSpriteFrameName("remove.png");
    removeOff->setColor(ccc3(102,102,102));
    pRemoveButton =
        CCMenuItemSprite::create(remove, removeOff, this, menu_selector(DetailLayer::remove));
    pRemoveButton->setAnchorPoint(ccp(0,0));
    pRemoveButton->setPosition(ccp(222 - 68, 114));
    pRemoveButton->setVisible(this->_equipment->isEquipped());
    
    CCMenu* pMenu = CCMenu::create(pEquipButton, pRemoveButton, pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
}

CCLabelTTF* DetailLayer::addStatusObject(std::string name, CCString* string, CCPoint position, CCNode* node){
    CCLabelTTF* pLabel = CCLabelTTF::create(name.c_str(), "arial", 10);
    pLabel->setColor(ccc3(0,0,0));
    pLabel->setAnchorPoint(ccp(0, 0));
    pLabel->setPosition(ccp(10, position.y - 15 * (_lineNum)));
    node->addChild(pLabel);
    
    CCLabelTTF* pStatus = CCLabelTTF::create(string->getCString(), "arial", 10);
    pStatus->setColor(ccc3(0,0,0));
    pStatus->setAnchorPoint(ccp(0,0));
    pStatus->setPosition(ccp(position.x + 100, position.y - 15 * (_lineNum)));
    node->addChild(pStatus);
    _lineNum++;
    return pStatus;
}

CCLabelTTF* DetailLayer::addStatusObject(std::string name, int status, int current, CCPoint position, CCNode* node){
    CCLOG("lineNum:%d", _lineNum);
    CCLabelTTF* pLabel = CCLabelTTF::create(name.c_str(), "arial", 10);
    pLabel->setColor(ccc3(0,0,0));
    pLabel->setAnchorPoint(ccp(0, 0));
    pLabel->setPosition(ccp(10, position.y - 15 * (_lineNum)));
    node->addChild(pLabel);
    
    CCLabelTTF* pStatus = CCLabelTTF::create(CCString::createWithFormat(": %d (%d)", status, current)->getCString(), "arial", 10);
    pStatus->setColor(ccc3(0,0,0));
    pStatus->setAnchorPoint(ccp(0,0));
    pStatus->setPosition(ccp(position.x + 100, position.y - 15 * (_lineNum)));
    node->addChild(pStatus);
    _lineNum++;
    return pStatus;
}


void DetailLayer::close(){
    this->removeFromParentAndCleanup(true);
}

bool DetailLayer::ccTouchBegan(CCTouch *touch, CCEvent* event){
    return true;
}

void DetailLayer::equip(){
    pEquipButton->setVisible(false);
    pRemoveButton->setVisible(true);
    _belongings->set(this->_equipment);
    this->_equipment->setEquipped(true);
}

void DetailLayer::remove(){
    pEquipButton->setVisible(true);
    pRemoveButton->setVisible(false);
    _belongings->unset(this->_equipment);
    this->_equipment->setEquipped(false);
}

void DetailLayer::updateStatus(cocos2d::CCLabelTTF *label, int status, int current){
   label->setString(CCString::createWithFormat(": %d (%d)", status, current)->getCString());
}

void DetailLayer::update(){
    CCString* equipStatus;
    Equipment* _current = _belongings->get(_equipment->getCategory());
    
    this->updateStatus(baseDamageLabel, _equipment->getBaseDamage(), _current->getBaseDamage());
    this->updateStatus(swordDamageLabel, _equipment->getSwordDamage(), _current->getSwordDamage());
    this->updateStatus(shieldHpLabel, _equipment->getShieldMaxHp(), _current->getShieldMaxHp());
    this->updateStatus(shieldRefillLabel, _equipment->getShieldRefill(), _current->getShieldRefill());
    this->updateStatus(potionRecoverLabel, _equipment->getPotionRecover(), _current->getPotionRecover());
    this->updateStatus(maxHpLabel, _equipment->getMaxHp(), _current->getMaxHp());
    this->updateStatus(coinAdditionLabel, _equipment->getCoinAddition(), _current->getCoinAddition());
    this->updateStatus(strengthLabel, _equipment->getStrength(), _current->getStrength());
    this->updateStatus(defenseLabel, _equipment->getDefense(), _current->getDefense());
    this->updateStatus(dexterityLabel, _equipment->getDexterity(), _current->getDexterity());
    this->updateStatus(vitalityLabel, _equipment->getVitality(), _current->getVitality());
    if (_equipment->isEquipped()){
        equipStatus = CCString::create(": on");
    } else {
        equipStatus = CCString::create(": off");
    }
    equipStatusLabel->setString(equipStatus->getCString());
}