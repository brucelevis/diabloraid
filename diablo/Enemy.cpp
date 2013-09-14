//
//  Enemy.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#include "Enemy.h"

Enemy::Enemy(int _hp, int str, int def){
    _connectType = 1;
    hp = new HitPoint(_hp);
    strength = new Strength(str);
    defense = new Defense(def);
}

Enemy* Enemy::createWithSpriteFrameName(const char *pszSpriteFrameName, int _hp, int _str, int _def){
    Enemy* sprite = new Enemy(_hp, _str, _def);
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        sprite->currentHpLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->hp->getCurrentHp())->getCString(), "arial", 10);
        sprite->currentHpLabel->setPosition(ccp(48, 0));
        sprite->addChild(sprite->currentHpLabel);
        
        sprite->defenseLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->defense->getMax())->getCString(), "arial", 10);
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
    this->switchOn();
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
    //攻撃は、軽減される。
    int damage = strength->getValue() - player->defense->getCurrent();
    if(damage < 0){
        damage = 0;
    }
    player->defense->damage(strength->getValue());
    player->damage(damage);
}

Enemy::~Enemy(){
    delete strength;
    delete defense;
    delete hp;
}

