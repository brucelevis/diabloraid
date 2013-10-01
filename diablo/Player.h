//
//  Player.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#ifndef __diablo__Player__
#define __diablo__Player__

#include <iostream>
#include "cocos2d.h"
#include "HitPoint.h"
#include "ShieldStatus.h"
#include "BaseDamage.h"
#include "SwordDamage.h"
#include "PotionRecover.h"
#include "ShieldRefill.h"
#include "Level.h"
#include "Events.h"
#include "EventFactory.h"
using namespace cocos2d;

class Player{
    CCArray* accumDamages; //パネルをタッチしている間の累積ダメージを保存する。push popで簡単に処理するため
    Events* events;
    HitPoint* hp;
    ShieldStatus* shieldStatus;
    BaseDamage* baseDamage;
    SwordDamage* swordDamage;
    PotionRecover* potionRecover;
    ShieldRefill* shieldRefill;
    Level* level;
public:
    int getCurrentHp();
    int getMaxHp();
    
    int getShieldCurrentHp();
    int getShieldMaxHp();
    
    int getCurrentLevel();
    int getCurrentExp();
    
    int getPotionRecover();
    
    int getShieldRefill();
    
    int getSwordDamage();
    
    void damage(int v);
    void damageToShield(int v);
    
    void recover(int v);
    void recoverShield(int v);
    
    bool isAlive();
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
    
    int getTotalDamage(); //今回の累積ダメージを取得する。
    void addExp(int addedExp);
    void pushLevelUpEvent();
    Events* getEvent();
    Player();
    ~Player(void);
};
#endif /* defined(__diablo__Player__) */