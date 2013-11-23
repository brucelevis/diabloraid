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
#include "ModelManager.h"
#include "PanelDataManager.h"
#include "EnemyDataManager.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "PanelData.h"
#include "Potion.h"
#include "Coin.h"
#include "Sword.h"
#include "Shield.h"
#include "Stair.h"
#include "Floor.h"
#include "Treasure.h"

class PanelSpriteFactory {
public:
    static PanelSprite* createWithFloor(Floor* floor);
    static PanelData* createPanelDataWithFloor(Floor* floor); //データを生成する。
    static PanelSprite* createByPanelData(PanelData* panelData);
    static CCString* convertToPanelName(int panelType);
    static int convertToPanelType(std::string panelName);
};

#endif /* defined(__diablo__PanelSpriteFactory__) */
