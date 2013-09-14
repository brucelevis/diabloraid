//
//  Enemy.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#ifndef __diablo__Enemy__
#define __diablo__Enemy__

#include <iostream>
#include "HitPoint.h"
#include "PanelSprite.h"
#include "Player.h"
#include "Strength.h"
#include "Defense.h"

class Enemy : public PanelSprite
{
    HitPoint* hp;
    Strength* strength; //Strengthクラスを一応使う
    Defense*  defense;  //Defenseクラスを一応使う
    CCLabelTTF* currentHpLabel; //今のhpの表示
    CCLabelTTF* strengthLabel;  //攻撃力の表示
    CCLabelTTF* defenseLabel;  //攻撃力の表示
public:
    static Enemy* createWithSpriteFrameName(const char *pszSpriteFrameName, int _hp, int _str, int _def);
    void attack(Player* player); //Playerも攻撃対象とかの抽象クラスにするかもね。
    void setRemoved(Player* player);
    void actionGotoRemoved(Player* player);
    void actionTouched(Player* player);
    void actionUntouched(Player* player);
    void setKilledImage();
    void update();
    Enemy(int hp, int str, int def);
    ~Enemy(void);
};

#endif /* defined(__diablo__Enemy__) */
