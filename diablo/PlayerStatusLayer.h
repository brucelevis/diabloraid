//
//  PlayerStatusLayer.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/04.
//
//

#ifndef __diablo__PlayerStatusLayer__
#define __diablo__PlayerStatusLayer__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;

class PlayerStatusLayer : public CCLayer{
    CCMenuItemSprite* pOkButton;
    CCScene* _scene;
    Player* _player;
    int _lineNum;
public:
    virtual bool init();
    
    static CCScene* scene();
    static PlayerStatusLayer* layer();
    static PlayerStatusLayer* layerWithPlayer(Player* player);
    
    void setScene(CCScene* scene);
    CCScene* getScene();
    
    void addWindowObjects();
    void addStatusObject(std::string name, int status, int equipmentStatus, CCPoint position, CCNode* node);
    
    void close();
    
    void update();
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    CREATE_FUNC(PlayerStatusLayer);
};

#endif /* defined(__diablo__PlayerStatusLayer__) */
