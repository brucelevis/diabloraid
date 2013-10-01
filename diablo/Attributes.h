//
//  Attributes.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#ifndef __diablo__Attributes__
#define __diablo__Attributes__

#include <iostream>
#include "HitPoint.h"
#include "ShieldStatus.h"
#include "BaseDamage.h"
#include "SwordDamage.h"
#include "PotionRecover.h"
#include "ShieldRefill.h"
#include "AttributeBase.h"
#include "Vitality.h"

class Attributes {
    HitPoint* hp;
    ShieldStatus* shieldStatus;
    BaseDamage* baseDamage;
    SwordDamage* swordDamage;
    PotionRecover* potionRecover;
    ShieldRefill* shieldRefill;
    AttributeBase* strength;
    AttributeBase* defense;
    Vitality* vitality;
    AttributeBase* dexterity;
    
public:
    Attributes();
    ~Attributes();
    
    int getCurrentHp();
    int getMaxHp();
    
    int getShieldCurrentHp();
    int getShieldMaxHp();
    
    int getCurrentLevel();
    int getCurrentExp();
    
    int getPotionRecover();
    
    int getShieldRefill();
    
    int getSwordDamage();
    
    int getBaseDamage();
    
    void damage(int v);
    void damageToShield(int v);
    
    void recover(int v);
    void recoverShield(int v);
    
    bool isAlive();
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
};

#endif /* defined(__diablo__Attributes__) */