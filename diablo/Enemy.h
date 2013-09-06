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

class Enemy : public PanelSprite
{
    HitPoint* hp;
    int strength; //TODO:statusクラスとかにかえる。とりあえず、ストレングスの数だけダメージ
public:
    static Enemy* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void attack(Player* player); //Playerも攻撃対象とかの抽象クラスにするかもね。
    Enemy();
    ~Enemy(void);
};

#endif /* defined(__diablo__Enemy__) */
