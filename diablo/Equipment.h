//
//  Equipment.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#ifndef __diablo__Equipment__
#define __diablo__Equipment__

#include <iostream>
#include "picojson.h"
#include "Util.h"
#include "cocos2d.h"
#include "Attributes.h"
using namespace cocos2d;

class Equipment : public CCObject{
    picojson::value _records;
    int id;
    int imageId;
    int imageColor;
    int isEquip;
    std::string name;
    std::string description;
    Attributes* attributes;
public:
    Equipment(picojson::object rec);
    ~Equipment();
    std::string getName();
    
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
    
    void setEquipped(bool _isEquipped);
    bool isEquipped();
    
    //for debug
    static Equipment* getMock();
};

#endif /* defined(__diablo__Equipment__) */
