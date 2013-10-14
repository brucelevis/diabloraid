//
//  PanelSpriteFactory.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#ifndef __diablo__PanelSpriteFactory__
#define __diablo__PanelSpriteFactory__

#include <iostream>
#include "PanelSprite.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "Potion.h"
#include "Coin.h"
#include "Sword.h"
#include "Shield.h"
#include "Stair.h"
#include "Floor.h"
#include "FieldModel.h"

class PanelSpriteFactory {
public:
    static PanelSprite* createWithFloor(Floor* floor);
};

#endif /* defined(__diablo__PanelSpriteFactory__) */
