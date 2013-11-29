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
#include "cocos2d.h"
#include "HitPoint.h"
#include "HungryPoint.h"
#include "ShieldStatus.h"
#include "BaseDamage.h"
#include "SwordDamage.h"
#include "PotionRecover.h"
#include "ShieldRefill.h"
#include "AttributeBase.h"
#include "Vitality.h"

using namespace cocos2d;

class Attributes {
    HitPoint* hp;
    HungryPoint* hungryP;
    ShieldStatus* shieldStatus;
    BaseDamage* baseDamage;
    SwordDamage* swordDamage;
    PotionRecover* potionRecover;
    ShieldRefill* shieldRefill;
    AttributeBase* strength;
    AttributeBase* defense;
    Vitality* vitality;
    AttributeBase* dexterity;
    AttributeBase* coinAddition;
public:
    Attributes();
    ~Attributes();
    
    static Attributes* createWithDefault();
    static Attributes* createWithCCDictionary(CCDictionary* dictionary);
    static Attributes* _create(int _hp,
                        int _ss,
                        int _bd,
                        int _sd,
                        int _pr,
                        int _sr,
                        int _ca,
                        int _str,
                        int _def,
                        int _vit,
                        int _dex,
                        int _hungryP);
    
    int getCurrentHp();
    int getMaxHp();
    
    int getCurrentHungryP();
    int getMaxHungryP();
    
    int getShieldCurrentHp();
    int getShieldMaxHp();
    
    int getCurrentLevel();
    int getCurrentExp();
    
    int getPotionRecover();
    
    int getShieldRefill();
    
    int getSwordDamage();
    
    int getBaseDamage();
    
    int getCoinAddition();
    
    int getStrength();
    int getDefense();
    int getDexterity();
    int getVitality();
    
    void damage(int v);
    void damageToShield(int v);
    
    void reduceHungryP(int v);
    bool hasHungryP();
    bool isHungryMiddle(); //お腹が減ってきた……。
    bool isHungryBig();    //ハラペコで　目がまわってきた……。
    bool isHungryToDeath(); //だめだ！　もう倒れそうだ！早く……何か　食べないと……。飢え死にしてしまう！
    
    void recover(int v);
    void recoverAllHp();
    void recoverShield(int v);
    
    void recoverHungryP(int v);
    
    bool isAlive();
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
    
    void addStrength(int v);
    void addDefense(int v);
    void addDexterity(int v);
    void addVitality(int v);
    
    // for debug
    static Attributes* getAttributesMock();
};

#endif /* defined(__diablo__Attributes__) */