//
//  EquipmentDetail.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/16.
//
//

#ifndef __diablo__EquipmentDetail__
#define __diablo__EquipmentDetail__

#include <iostream>
#include "UserItem.h"
#include "DetailBase.h"
#include "cocos2d.h"

using namespace cocos2d;

class EquipmentDetail :public DetailBase {
    CCMenuItemSprite* pEquipButton;
    CCMenuItemSprite* pRemoveButton;
    CCLabelTTF* equipStatusLabel;
    CCLabelTTF* baseDamageLabel;
    CCLabelTTF* swordDamageLabel;
    CCLabelTTF* shieldHpLabel;
    CCLabelTTF* shieldRefillLabel;
    CCLabelTTF* maxHpLabel;
    CCLabelTTF* potionRecoverLabel;
    CCLabelTTF* coinAdditionLabel;
    CCLabelTTF* strengthLabel;
    CCLabelTTF* defenseLabel;
    CCLabelTTF* dexterityLabel;
    CCLabelTTF* vitalityLabel;
    int _lineNum;
       
    void remove();
    void equip();
    
    
    UserItem* userItem;
    Belongings* belongings;
public:
    static EquipmentDetail* createWithUserItemAndBelongings(UserItem* userItem, Belongings* belongings);
    void update();
    void addWindowObjects();
    CCLabelTTF* addStatusObject(std::string name, CCString* string, CCPoint position, CCNode* node);
    CCLabelTTF* addStatusObject(std::string name, int status, int current, CCPoint position, CCNode* node);
    void updateStatus(CCLabelTTF* label, int status,int current);
    EquipmentDetail(UserItem* userItem, Belongings* belongings);
    ~EquipmentDetail();
};

#endif /* defined(__diablo__EquipmentDetail__) */