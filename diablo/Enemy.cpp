//
//  Enemy.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#include "Enemy.h"

Enemy::Enemy(EnemyMaster* enemy){
    _connectType = 1;
    _isEnemy = true;
    hp = new HitPoint(enemy->getHp());
    baseDamage = new BaseDamage(enemy->getAttack());
    shieldStatus = new ShieldStatus(enemy->getDef());
    exp = enemy->getExp();
}

Enemy* Enemy::createWithEnemyMaster(EnemyMaster* enemy){
    Enemy* sprite = new Enemy(enemy);
    
    const char *pszSpriteFrameName = enemy->getName().c_str();
    
    sprite->_panelName = pszSpriteFrameName;
    if(sprite && sprite->initWithSpriteFrameName((sprite->_panelName + ".png").c_str())){
        
        sprite->setCanExistNum(enemy->getMaxExistsNum());
        sprite->currentHpLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->hp->getCurrentHp())->getCString(), "arial", 10);
        sprite->currentHpLabel->setPosition(ccp(48, 0));
        sprite->addChild(sprite->currentHpLabel);
        
        sprite->shieldStatusLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->shieldStatus->getMax())->getCString(), "arial", 10);
        sprite->shieldStatusLabel->setPosition(ccp(48, 27));
        sprite->addChild(sprite->shieldStatusLabel);
        sprite->baseDamageLabel = CCLabelTTF::create(CCString::createWithFormat("%d", sprite->baseDamage->getValue())->getCString(), "arial", 10);
        sprite->baseDamageLabel->setPosition(ccp(48, 54));
        sprite->addChild(sprite->baseDamageLabel);
        
        sprite->_touchRect = *new CCRect();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

Enemy* Enemy::createWithEnemyData(EnemyData *enemyData){
    Enemy* sprite = createWithEnemyMaster(enemyData->master);
    sprite->hp->setCurrentHp(enemyData->getCurrentHp());
    return sprite;
}

//このタイミングでダメージを与える。
void Enemy::actionGotoRemoved(Player* player){
    hp->reduce(player->getTotalDamage());
    if ( this->_willRemoved ){
        //敵を倒した時だけ。
        player->addExp(exp);
    }
}

void Enemy::actionTouched(Player* player){
    if(hp->getCurrentHp() - player->getTotalDamage() <= 0){
        this->setKilledImage();
    } else {
        this->switchOn();
    }
}

void Enemy::actionAttack(){
    CCScaleBy* scaleBySmall     = CCScaleBy::create(0.2, 0.5);
    CCScaleBy* scaleByBig       = CCScaleBy::create(0.1, 4.0);
    CCScaleBy* scaleByCurrent   = CCScaleBy::create(0.1, 0.5);
    CCTintBy*  tintByRed        = CCTintBy::create(0.1, 0, 255, 255);
    //CCTintBy*  tintByNormal     = CCTintBy::create(0.1, -255, 0,0);
    
    this->runAction(CCSequence::create(scaleBySmall, CCSpawn::createWithTwoActions(scaleByBig, tintByRed), scaleByCurrent, NULL));
}

void Enemy::actionUntouched(Player* player){
    this->switchOn();
}

// override
void Enemy::setRemoved(Player* player){
    // hpが今回の攻撃で0を下回る時だけ_willRemovedをたてる。
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

bool Enemy::isEnemy(){
    return _isEnemy;
}

void Enemy::update(){
    PanelSprite::update();
    if(!_isActive){
        return;
    }
    this->currentHpLabel->setString((CCString::createWithFormat("%d", this->hp->getCurrentHp())->getCString()));
}

void Enemy::attack(Player* player){
    if(!_isActive){
        return;
    }
    
    //攻撃は、軽減される。
    int damage = baseDamage->getValue() - player->getShieldCurrentHp();
    if(damage < 0){
        damage = 0;
    }
    this->actionAttack();
    player->damageToShield(baseDamage->getValue());
    player->damage(damage);
}

Enemy::~Enemy(){
    delete baseDamage;
    delete shieldStatus;
    delete hp;
}

