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
using namespace cocos2d;


class DetailLayer : public CCLayer{
    CCMenuItemSprite* pOkButton;
    CCMenuItemSprite* pEquipButton;
    CCMenuItemSprite* pRemoveButton;
    CCLabelTTF* equipStatusLabel;
    CCScene* _scene;
    Equipment* _equipment;
    int _lineNum;
public:
    virtual bool init();
    
    static CCScene* scene();
    static DetailLayer* layer();
    static DetailLayer* layerWithEquipment(Equipment* equipment);
    
    void setScene(CCScene* scene);
    CCScene* getScene();
    
    void addWindowObjects();
    void addStatusObject(std::string name, CCString* string, CCPoint position, CCNode* node);
    void addStatusObject(std::string name, int status, CCPoint position, CCNode* node);
    
    void close();
    void remove();
    void equip();
    
    void update();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    CREATE_FUNC(DetailLayer);
};

#endif /* defined(__diablo__DetailLayer__) */
