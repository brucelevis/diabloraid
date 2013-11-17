//
//  UsableDetail.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/16.
//
//

#include "UsableDetail.h"

UsableDetail *UsableDetail::createWithUserItemAndPlayer(UserItem* userItem, Player* player){
	UsableDetail * pRet = new UsableDetail(userItem, player);
	pRet->autorelease();
	return pRet;
}

UsableDetail::UsableDetail(UserItem* userItem, Player* player){
    this->userItem = userItem;
    this->player = player;
}

UsableDetail::~UsableDetail(){
}

void UsableDetail::addWindowObjects(){
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
    
    CCLabelTTF* nameLabel = CCLabelTTF::create(this->userItem->getName().c_str(), "arial", 15);
    nameLabel->setColor(ccc3(0,0,0));
    nameLabel->setAnchorPoint(ccp(0, 0));
    nameLabel->setPosition(ccp(10,  layer->getContentSize().height - 50));
    layer->addChild(nameLabel);
    
    CCLayerColor *descriptionBg = CCLayerColor::create(ccc4(180, 180, 180, 255));
    descriptionBg->setContentSize(CCSizeMake(244, 174));
    descriptionBg->setAnchorPoint(ccp(0,0));
    descriptionBg->setPosition(ccp(38,178));
    this->addChild(descriptionBg);
    
    CCLabelTTF* descLabel = CCLabelTTF::create(this->userItem->getDescription().c_str(), "arial", 15);
    descLabel->setColor(ccc3(0,0,0));
    descLabel->setAnchorPoint(ccp(0, 0));
    descLabel->setPosition(ccp(5, descriptionBg->getContentSize().height - 30));
    descriptionBg->addChild(descLabel);
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(layer->getContentSize().width / 2, layer->getContentSize().height - 10) );

    // add the label as a child to this layer
    
    layer->addChild(pLabel, 1);
    CCSprite* equip = CCSprite::createWithSpriteFrameName("use.png");
    CCSprite* equipOff = CCSprite::createWithSpriteFrameName("use.png");
    equipOff->setColor(ccc3(102,102,102));
    pUseButton =
        CCMenuItemSprite::create(equip, equipOff, this, menu_selector(UsableDetail::use));
    pUseButton->setAnchorPoint(ccp(0,0));
    pUseButton->setPosition(ccp(222 - 68, 114));
    
    CCMenu* pMenu = CCMenu::create(pUseButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
}

void UsableDetail::update(){
}

void UsableDetail::use(){
    //TODO 薬草、おとぎりそう以外も対応する。
    player->recover(userItem->getValue());
}