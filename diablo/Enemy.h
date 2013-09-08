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
    CCArray* accumDamages; //パネルをタッチしている間の累積ダメージを保存する。push popで簡単に処理するため
public:
    static Enemy* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
    int getTotalDamage(); //今回の累積ダメージを取得する。
    void attack(Player* player); //Playerも攻撃対象とかの抽象クラスにするかもね。
    void setRemoved();
    Enemy();
    ~Enemy(void);
};

#endif /* defined(__diablo__Enemy__) */
