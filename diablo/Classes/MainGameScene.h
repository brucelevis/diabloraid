#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PanelSprite.h"
#include "Field.h"
#include "Player.h"
#include "TurnManager.h"
#include "BagListLayer.h"
#include "EventFactory.h"
#include "Events.h"
#include "EquipmentList.h"
#include "PlayerStatusLayer.h"
using namespace cocos2d;
class TurnManager;

class MainGameScene : public cocos2d::CCLayer
{
    Field *_field;
    Player* _player;
    bool _touching;
    bool _onTurn;
    EquipmentList* _equipmentList;
    TurnManager* _turnManager;
    CCLabelTTF* HpLabel;
    CCLabelTTF* ShieldLabel;
    CCLabelTTF* TurnLabel;
    CCLabelTTF* FloorLabel;
    CCLabelTTF* DamageLabel;
    CCLabelTTF* levelLabel;
    CCLabelTTF* budgetLabel;
    Events* _events;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    bool showDamage(PanelSprite* panel);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    void pushLevelUp();
    CREATE_FUNC(MainGameScene);
    void update(float dt);
    void watchPlayerLevelUp();
    void pushLevelUpEvent();
    void pushStatusScene();
    void pushEquipScene();
    
    void handleEvents();
};

#endif // __HELLOWORLD_SCENE_H__
