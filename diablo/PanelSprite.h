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
using namespace cocos2d;

class PanelSprite : public cocos2d::CCSprite
{
    float _deltaY;
    float _velocity;
    bool _isOn; //on状態か
    float _size;
    void _switchOn(bool isOn);
    CCDictionary* _displayedDirection;
    CCArray* _directionSprites; //方向の絵を保持する。
protected:
    bool _willRemoved; //消去されるflag
    int _connectType; //つながるかどうかを保存する。
public:
    std::string _panelName;
    CCRect _touchRect;
    PanelSprite();
    ~PanelSprite(void);
    
    static PanelSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    std::string getPanelName();
    void setSize(float size); //サイズをsetする。
    bool isConnectable(PanelSprite* panel); //自身のconnectTypeと比較して、つながるかどうかチェック
    bool isSamePanel(std::string panelName);
    bool isNextPanel(PanelSprite* panel);
    int  getDirection(PanelSprite* panel);
    virtual void setRemoved(Player* player);
    void setTouched();
    void setUnTouched();
    void switchOn();  //on画像に変更する。
    void switchOff(); //off画像に変更する。
    virtual void update(); //更新
    
    virtual void actionRemoved(Player* player);
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
