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
#include "UserItem.h"

class UserItem;

class Belongings{
    UserItem* _null;
    UserItem* sword;
    UserItem* shield;
    UserItem* armor;
public:
    void set(UserItem* equipment);
    void unset(UserItem* equipment);
    bool isEquipped(UserItem* equipment); //その装備を装備しているかどうかを返す。
    UserItem* get(int category);//そのカテゴリの装備を取得する。
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
