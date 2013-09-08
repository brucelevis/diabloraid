//
//  Enemy.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#include "Enemy.h"

Enemy::Enemy(){
    hp = new HitPoint();
    _connectType = 1;
    strength = new Strength(5);
    defense = new Defense(5);
}

Enemy* Enemy::createWithSpriteFrameName(const char *pszSpriteFrameName){
    Enemy* sprite = new Enemy();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->currentHpLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->hp->getCurrentHp())->getCString(), "arial", 10);
        sprite->currentHpLabel->setPosition(ccp(48, 0));
        sprite->addChild(sprite->currentHpLabel);
        
        sprite->defenseLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->defense->getValue())->getCString(), "arial", 10);
        sprite->defenseLabel->setPosition(ccp(48, 27));
        sprite->addChild(sprite->defenseLabel);
        sprite->strengthLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->strength->getValue())->getCString(), "arial", 10);
        sprite->strengthLabel->setPosition(ccp(48, 54));
        sprite->addChild(sprite->strengthLabel);
        
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

//このタイミングでダメージを与える。
void Enemy::actionGotoRemoved(Player* player){
    hp->reduce(player->getTotalDamage());
}

void Enemy::actionTouched(Player* player){
    if(hp->getCurrentHp() - player->getTotalDamage() <= 0){
        this->setKilledImage();
    } else {
        this->switchOn();
    }
}

void Enemy::actionUntouched(Player* player){
    if(hp->getCurrentHp() - player->getTotalDamage() > 0){
        this->switchOn();
    }
}

// override
void Enemy::setRemoved(Player* player){
    // hpが今回の攻撃で0を下回る時だけ_willRemovedをたてる。
    // プレイヤーからのダメージをどう知るか。// Enemyがplayerを知っている？
    if(hp->getCurrentHp() - player->getTotalDamage() <= 0){
        _willRemoved = true;
    }
}


void Enemy::setKilledImage(){
    std::string frameName;
    frameName = (this->_panelName + "_batsu.png").c_str();
    
    CCSpriteFrame* _frame;
    _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
    this->setTexture(_frame->getTexture());
    this->setTextureRect(_frame->getRect(), false, CCSize(_size, _size));
}

void Enemy::update(){
    PanelSprite::update();
    this->currentHpLabel->setString((CCString::createWithFormat("%d", this->hp->getCurrentHp())->getCString()));
}

void Enemy::attack(Player* player){
    player->damage(strength->getValue());
}

Enemy::~Enemy(){
    delete strength;
    delete defense;
    delete hp;
}

