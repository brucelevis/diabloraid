//
//  EquipmentMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/09.
//
//

#ifndef __diablo__EquipmentMaster__
#define __diablo__EquipmentMaster__

#include <iostream>
#include "Util.h"
#include "ModelInterface.h"
#include "HavingMasterInterface.h"
#include "picojson.h"
#include "Attributes.h"

class EquipmentMaster : public HavingMasterInterface, public ModelInterface {
    picojson::value _records;
    int _id;
    std::string _name;
    int type;
    int value;
    int imageId;
    int imageColor;
    std::string description;
    Attributes* attributes;
    int _category;
public:
    static EquipmentMaster* getById(int v);
    std::string getName();
    int getId();
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
    
    int getCategory();
    EquipmentMaster(int v);
    ~EquipmentMaster();
};

#endif /* defined(__diablo__EquipmentMaster__) */
