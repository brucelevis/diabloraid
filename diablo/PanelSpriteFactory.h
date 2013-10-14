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
#include "Potion.h"
#include "Coin.h"
#include "Sword.h"
#include "Shield.h"
#include "Stair.h"
#include "Floor.h"

class PanelSpriteFactory {
public:
    static PanelSprite* createWithFloorAndPanelName(Floor* floor, std::string panelName);
};

#endif /* defined(__diablo__PanelSpriteFactory__) */
