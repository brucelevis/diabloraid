//
//  FloorField.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/26.
//
//

#ifndef __diablo__FloorField__
#define __diablo__FloorField__

#include <iostream>
#include "Floor.h"
#include "FloorFieldModel.h"
#include "Field.h"
#include "cocos2d.h"
#include "PanelSpriteFactory.h"
#include "PanelData.h"

using namespace cocos2d;

class FloorField{
public:
    static FloorFieldModel* createInitialFloor(Floor* floor);           //map全体を生成する。
};

#endif /* defined(__diablo__FloorField__) */