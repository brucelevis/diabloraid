//
//  UserItems.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/11.
//
//

#ifndef __diablo__UserItems__
#define __diablo__UserItems__

#include <iostream>
#include "cocos2d.h"
#include "UserItem.h"
#include "Util.h"
#include "Belongings.h"

using namespace std;
using namespace cocos2d;

class UserItems : public CCArray {
    Belongings* _equipped; //装備しているものだけを内部的に持っとく。
    static UserItems* create();
public:
    static UserItems* getAll();
    Belongings* getBelongings();
    void setBelongings();
    UserItems();
    ~UserItems();
    int getMaxHp();
    
    int getShieldMaxHp();
    
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
    void reload(); //装備が更新されたりすると、更新する。
};

#endif /* defined(__diablo__UserItems__) */
