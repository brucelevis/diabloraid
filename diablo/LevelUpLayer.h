//
//  LevelUpLayer.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/20.
//
//

#ifndef __diablo__LevelUpLayer__
#define __diablo__LevelUpLayer__

#include <iostream>
#include "cocos2d.h"
#include "StatusUpgrade.h"
#include "Events.h"
#include "Player.h"
#include "Attributes.h"

using namespace cocos2d;

class Events;
class LevelUpLayer : public CCLayer{
    CCArray* status;
    CCLabelTTF* remainings;
    StatusUpgrade *strength, *defense, *dexterity, *vitality;
    CCMenuItemSprite* pOkButton;
    int remain;
    CCScene* _scene;
    Events* _events;
    CCLayer* _parentLayer;
    Player* _player;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static LevelUpLayer* layer();
    static LevelUpLayer* layerWithAttributes(Attributes* attributes);
    static LevelUpLayer* layerWithPlayer(Player* player);
    static CCScene* scene();
    void addWidowObjects();//表示系のものは後で追加する。
    void setScene(CCScene* scene);
    void setCallback(Events* events, CCLayer* layer);
    CCScene* getScene();
    void update();
    void close();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    CREATE_FUNC(LevelUpLayer);
};

#endif /* defined(__diablo__LevelUpLayer__) */
