//
//  PanelSprite.h
//  diablo
//
//  Created by Kosuke Takami on 13/08/17.
//
//

#ifndef __diablo__PanelSprite__
#define __diablo__PanelSprite__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"
#include "PanelData.h"
using namespace cocos2d;

class PanelSprite : public cocos2d::CCSprite
{
    PanelData* _panelData;
    float _deltaY;
    float _velocity;
    bool _isOn; //on状態か
    bool _isVisible;
    bool _isEnemy;
    bool isTouchable;
    void _switchOn(bool isOn);
    int _canExistNum;
    CCDictionary* _displayedDirection;
    CCArray* _directionSprites; //方向の絵を保持する。
protected:
    bool _willRemoved; //消去されるflag
    bool _alreadyActionTouched;
    int _connectType; //つながるかどうかを保存する。
    float _size;
    bool _isActiveOnlyOnePanel;
    std::string _panelName;
    CCRect _touchRect;
public:
    PanelSprite();
    ~PanelSprite(void);
    
    void initialize();
    static PanelSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    std::string getPanelName();
    int getConnectType();
    void setSize(float size); //サイズをsetする。
    void setPanelData(PanelData* panelData);
    
    int getId();
    
    CCRect getRect();
    
    void setActiveState(bool isActiveState);
    
    bool isConnectable(PanelSprite* panel); //自身のconnectTypeと比較して、つながるかどうかチェック
    bool isSamePanel(std::string panelName);
    bool isNextPanel(PanelSprite* panel);
    bool isActiveOnlyOnePanel();
    void setCanExistNum(int v);
    virtual bool canBeAdded(int num); //現在の数を渡して存在出来るかチェックする。
    virtual bool isEnemy();
    virtual void setRemoved(Player* player);
    int  getDirection(PanelSprite* panel);
    void setUnremoved();
    void setTouched();
    void setUnTouched();
    void switchOn();  //on画像に変更する。
    void switchOff(); //off画像に変更する。
    virtual void update(); //更新
    
    virtual void actionGotoRemoved(Player* player); //タッチを離したときにタッチされているパネルに対して、取り除かれないとしても呼ばれる。
    virtual void actionRemoved(Player* player); //取り除かれたときに呼ばれる。
    virtual void actionTouched(Player* player); //タッチされたときに呼ばれる。
    virtual void actionUntouched(Player* player); //タッチが解除されたときによばれる。
    
    void pushDirectionSprite(int direction); //方向を表す数を受け取って画像を突っ込んで表示する。
    void popDirectionSprite(); //突っ込まれたDirection表記を一つpopする。
    void removeAllDirectionSprite(); //突っ込まれたDirection表記を全て消し去る。
    int hasArrow(); //矢印がある時は、その矢印のintを返す。
    
    bool isRemoved();
    void setDeltaY(float deltaY);
    void setPosition(const CCPoint& pos);
    bool move();
    CCRect getTouchRect();
};
#endif /* defined(__diablo__PanelSprite__) */
