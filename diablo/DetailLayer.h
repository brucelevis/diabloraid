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
#include "UserItem.h"
#include "Belongings.h"
#include "Const.h"
#include "DetailInterface.h"
#include "EquipmentDetail.h"

using namespace cocos2d;


class DetailLayer : public CCLayer{
    CCScene* _scene;
    UserItem* userItem;
    
    Belongings* belongings;
    EquipmentDetail* windowObjects;
    CCMenuItemSprite* pOkButton;
    void close();
public:
    virtual bool init();
    
    static CCScene* scene();
    static DetailLayer* layer();
    static DetailLayer* layerWithUserItem(UserItem* equipment);
    static DetailLayer* layerWithUserItemAndBelongings(UserItem* equipment, Belongings* belongings);
    void addCommonComponents();
    
    void setScene(CCScene* scene);
    CCScene* getScene();
    
    void addWindowObjects();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    void update();
    CREATE_FUNC(DetailLayer);
};

#endif /* defined(__diablo__DetailLayer__) */
