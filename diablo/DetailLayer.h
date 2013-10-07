//
//  DetailLayer.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#ifndef __diablo__DetailLayer__
#define __diablo__DetailLayer__

#include <iostream>
#include "cocos2d.h"
#include "Equipment.h"
#include "Belongings.h"
using namespace cocos2d;


class DetailLayer : public CCLayer{
    CCMenuItemSprite* pOkButton;
    CCMenuItemSprite* pEquipButton;
    CCMenuItemSprite* pRemoveButton;
    CCLabelTTF* equipStatusLabel;
    CCScene* _scene;
    Equipment* _equipment;
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
    
    Belongings* _belongings;
    int _lineNum;
public:
    virtual bool init();
    
    static CCScene* scene();
    static DetailLayer* layer();
    static DetailLayer* layerWithEquipment(Equipment* equipment);
    static DetailLayer* layerWithEquipmentAndBelongings(Equipment* equipment, Belongings* belongings);
    
    void setScene(CCScene* scene);
    CCScene* getScene();
    
    void addWindowObjects();
    CCLabelTTF* addStatusObject(std::string name, CCString* string, CCPoint position, CCNode* node);
    CCLabelTTF* addStatusObject(std::string name, int status, int current, CCPoint position, CCNode* node);
    void updateStatus(CCLabelTTF* label, int status,int current);
    
    void close();
    void remove();
    void equip();
    
    void update();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    CREATE_FUNC(DetailLayer);
};

#endif /* defined(__diablo__DetailLayer__) */
