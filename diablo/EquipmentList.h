//
//  EquipmentList.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#ifndef __diablo__EquipmentList__
#define __diablo__EquipmentList__

#include <iostream>
#include "cocos2d.h"
#include "Equipment.h"
#include "picojson.h"
#include "Util.h"
using namespace cocos2d;

class EquipmentList : public CCArray{
    EquipmentList* _equipped; //装備しているものだけを内部的に持っとく。
    EquipmentList* _getEquippedList();
public:
    static EquipmentList* getAll();
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

#endif /* defined(__diablo__EquipmentList__) */
