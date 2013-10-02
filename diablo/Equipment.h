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
using namespace cocos2d;

class Equipment : public CCObject{
    picojson::value _records;
    int id;
    int imageId;
    int imageColor;
    std::string name;
    std::string description;
    int hp;
    int baseDamage;
    int swordDamage;
    int potionRecover;
    int shieldStatus;
    int coinAddition;
    int strength;
    int defense;
    int dexterity;
    int vitality;
public:
    Equipment(picojson::object rec);
    ~Equipment();
    std::string getName();
    static CCArray* getAll();
};

#endif /* defined(__diablo__Equipment__) */
