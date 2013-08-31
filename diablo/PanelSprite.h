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
using namespace cocos2d;

class PanelSprite : public cocos2d::CCSprite
{
    float _deltaY;
    float _velocity;
    bool _willRemoved; //消去されるflag
    bool _isOn; //on状態か
    float _size;
    std::string _panelName;
    CCRect _touchRect;
    void _switchOn(bool isOn);
public:
    PanelSprite(void);
    ~PanelSprite(void);
    
    static PanelSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    std::string getPanelName();
    void setSize(float size); //サイズをsetする。
    bool isSamePanel(std::string panelName);
    bool isNextPanel(PanelSprite* panel);
    int  getDirection(PanelSprite* panel);
    void setRemoved();
    void setTouched();
    void setUnTouched();
    void switchOn(); //on画像に変更する。
    void switchOff(); //off画像に変更する。
    bool isRemoved();
    void setDeltaY(float deltaY);
    void setPosition(const CCPoint& pos);
    bool move();
    CCRect getTouchRect();
};
#endif /* defined(__diablo__PanelSprite__) */
