//
//  Belongings.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#ifndef __diablo__Belongings__
#define __diablo__Belongings__

#include <iostream>
#include "Equipment.h"

class Belongings {
    Equipment* _null;
    Equipment* sword;
    Equipment* shield;
    Equipment* armor;
public:
    void set(Equipment* equipment);
    void unset(Equipment* equipment);
    bool isEquipped(Equipment* equipment); //その装備を装備しているかどうかを返す。
    Equipment* get(int category);//そのカテゴリの装備を取得する。
    int getMaxHp();
    
    int getShieldMaxHp();
    
    int getPotionRecover();
    
    int getShieldRefill();
    
    int getSwordDamage();
    
    int getBaseDamage();
    
    int getCoinAddition();
    
    int getStrength();
    int getDefense();
    int getDexterity();
    int getVitality();
    Belongings();
    ~Belongings();
};

#endif /* defined(__diablo__Belongings__) */
