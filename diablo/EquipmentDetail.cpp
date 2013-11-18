//
//  EquipmentDetail.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/16.
//
//

#include "EquipmentDetail.h"

EquipmentDetail *EquipmentDetail::createWithUserItemAndBelongings(UserItem* userItem, Belongings* belongings)
{
	EquipmentDetail * pRet = new EquipmentDetail(userItem, belongings);
	pRet->autorelease();
	return pRet;
}

void EquipmentDetail::setParentLayer(DialogLayerInterface* layer){
    this->parentLayer = layer;
}


void EquipmentDetail::addWindowObjects(){
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
    
    this->addStatusObject("name", CCString::createWithFormat("%s", userItem->getName().c_str()), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    
    UserItem* _current = this->belongings->get(userItem->getCategory());
    baseDamageLabel = this->addStatusObject("base damage", userItem->getBaseDamage(), _current->getBaseDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    swordDamageLabel = this->addStatusObject("sword damage", userItem->getSwordDamage(), _current->getSwordDamage(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    shieldHpLabel = this->addStatusObject("shield hp", userItem->getShieldMaxHp(), _current->getShieldMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    shieldRefillLabel = this->addStatusObject("shield refill", userItem->getShieldRefill(), _current->getShieldRefill(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    maxHpLabel = this->addStatusObject("hp", userItem->getMaxHp(), _current->getMaxHp(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    potionRecoverLabel = this->addStatusObject("potion recover", userItem->getPotionRecover(), _current->getPotionRecover(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    coinAdditionLabel = this->addStatusObject("coin addition", userItem->getCoinAddition(), _current->getCoinAddition(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    strengthLabel = this->addStatusObject("strength", userItem->getStrength(), _current->getStrength(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    defenseLabel = this->addStatusObject("defense", userItem->getDefense(), _current->getDefense(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    dexterityLabel = this->addStatusObject("dexterity", userItem->getDexterity(), _current->getDexterity(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    vitalityLabel = this->addStatusObject("vitality", userItem->getVitality(), _current->getVitality(), ccp(0, layer->getContentSize().height - 35), (CCNode*) layer);
    
    CCLabelTTF* equipLabel = CCLabelTTF::create("eqiup","arial", 10);
    equipLabel->setColor(ccc3(0,0,0));
    equipLabel->setAnchorPoint(ccp(0, 0));
    equipLabel->setPosition(ccp(10, layer->getContentSize().height - 35 - 15 * (_lineNum)));
    layer->addChild(equipLabel);
    
    CCString* equipStatus;
    if (userItem->isEquipped()){
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
    this->pOkButton =
        CCMenuItemSprite::create(ok, okOff, this, menu_selector(EquipmentDetail::close));
    this->pOkButton->setAnchorPoint(ccp(0,0));
    this->pOkButton->setPosition(ccp(222, 114));
    
    CCSprite* equip = CCSprite::createWithSpriteFrameName("equip.png");
    CCSprite* equipOff = CCSprite::createWithSpriteFrameName("equip.png");
    equipOff->setColor(ccc3(102,102,102));
    pEquipButton =
        CCMenuItemSprite::create(equip, equipOff, this, menu_selector(EquipmentDetail::equip));
    pEquipButton->setAnchorPoint(ccp(0,0));
    pEquipButton->setPosition(ccp(222 - 68, 114));
    pEquipButton->setVisible(!this->userItem->isEquipped());
    
    CCSprite* remove = CCSprite::createWithSpriteFrameName("remove.png");
    CCSprite* removeOff = CCSprite::createWithSpriteFrameName("remove.png");
    removeOff->setColor(ccc3(102,102,102));
    pRemoveButton =
        CCMenuItemSprite::create(remove, removeOff, this, menu_selector(EquipmentDetail::remove));
    pRemoveButton->setAnchorPoint(ccp(0,0));
    pRemoveButton->setPosition(ccp(222 - 68, 114));
    pRemoveButton->setVisible(this->userItem->isEquipped());
    
    CCMenu* pMenu = CCMenu::create(pEquipButton, pRemoveButton, pOkButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
}

CCLabelTTF* EquipmentDetail::addStatusObject(std::string name, CCString* string, CCPoint position, CCNode* node){
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

CCLabelTTF* EquipmentDetail::addStatusObject(std::string name, int status, int current, CCPoint position, CCNode* node){
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

void EquipmentDetail::updateStatus(cocos2d::CCLabelTTF *label, int status, int current){
   label->setString(CCString::createWithFormat(": %d (%d)", status, current)->getCString());
}

void EquipmentDetail::close(){
    if(this->parentLayer){
        this->parentLayer->close();
    }
}


void EquipmentDetail::equip(){
    pEquipButton->setVisible(false);
    pRemoveButton->setVisible(true);
    belongings->set(this->userItem);
    this->userItem->setEquipped(true);
}

void EquipmentDetail::remove(){
    pEquipButton->setVisible(true);
    pRemoveButton->setVisible(false);
    this->belongings->unset(this->userItem);
    this->userItem->setEquipped(false);
}

void EquipmentDetail::update(){
    CCString* equipStatus;
    UserItem* _current = belongings->get(userItem->getCategory());
    
    this->updateStatus(baseDamageLabel, userItem->getBaseDamage(), _current->getBaseDamage());
    this->updateStatus(swordDamageLabel, userItem->getSwordDamage(), _current->getSwordDamage());
    this->updateStatus(shieldHpLabel, userItem->getShieldMaxHp(), _current->getShieldMaxHp());
    this->updateStatus(shieldRefillLabel, userItem->getShieldRefill(), _current->getShieldRefill());
    this->updateStatus(potionRecoverLabel, userItem->getPotionRecover(), _current->getPotionRecover());
    this->updateStatus(maxHpLabel, userItem->getMaxHp(), _current->getMaxHp());
    this->updateStatus(coinAdditionLabel, userItem->getCoinAddition(), _current->getCoinAddition());
    this->updateStatus(strengthLabel, userItem->getStrength(), _current->getStrength());
    this->updateStatus(defenseLabel, userItem->getDefense(), _current->getDefense());
    this->updateStatus(dexterityLabel, userItem->getDexterity(), _current->getDexterity());
    this->updateStatus(vitalityLabel, userItem->getVitality(), _current->getVitality());
    if (userItem->isEquipped()){
        equipStatus = CCString::create(": on");
    } else {
        equipStatus = CCString::create(": off");
    }
    equipStatusLabel->setString(equipStatus->getCString());
}

EquipmentDetail::EquipmentDetail(UserItem* userItem, Belongings* belongings){
    this->userItem = userItem;
    this->belongings = belongings;
}

EquipmentDetail::~EquipmentDetail(){
}