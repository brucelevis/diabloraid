//
//  UserItem.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/07.
//
//

#ifndef __diablo__UserItem__
#define __diablo__UserItem__

#include <iostream>
#include <map>
#include "Util.h"
#include "picojson.h"
#include "ModelManager.h"
#include "HavingMasterInterface.h"
#include "ItemMaster.h"
#include "EquipmentMaster.h"
#include "cocos2d.h"
#include "Const.h"

using namespace std;
using namespace cocos2d;

class UserItem : public CCObject{
    
private:
    static int seqId;
    int getSeqId();
    int id;
    int type;
    int itemId;
    bool isEquip;
    HavingMasterInterface* master;
public:
    static HavingMasterInterface* createMaster(UserItem *userItem);
    int getId();
    int getType();
    int getItemId();
    bool isEquipped();
    bool isEquipment();
    
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
    void setMaster(HavingMasterInterface* master);
    std::string getName();
    void setEquipped(bool _isEquipped);
    UserItem(map<string, string> entity);
    static UserItem* getMock(int type);
    UserItem();
    ~UserItem();
};

#endif /* defined(__diablo__UserItem__) */