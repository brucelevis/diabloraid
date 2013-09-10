//
//  TouchedPanels.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__TouchedPanels__
#define __diablo__TouchedPanels__

#include <iostream>
#include "cocos2d.h"
#include "PanelSprite.h"
#include "Player.h"
using namespace cocos2d;

//タッチされているパネルに対して何かするクラス
class TouchedPanels : public CCArray {
public:
    void setRemoved(Player* player);
    void initialize();
    void showDirections();
    void push(PanelSprite* panel, Player* player);
    void pop(Player* player);
    void popTo(PanelSprite* panel, Player* player);
};
#endif /* defined(__diablo__TouchedPanels__) */