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
using namespace cocos2d;

//タッチされているパネルに対して何かするクラス
class TouchedPanels : public CCArray {
public:
    void setRemoved();
    void push(PanelSprite* panel);
    void showDirections();
    PanelSprite* popTo(PanelSprite* panel);
};
#endif /* defined(__diablo__TouchedPanels__) */