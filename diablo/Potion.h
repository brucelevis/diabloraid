//
//  Potion.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#ifndef __diablo__Potion__
#define __diablo__Potion__

#include <iostream>
#include "PanelSprite.h"
#include "Player.h"

class Potion : public PanelSprite{
public:
    static Potion* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void recover(Player* player); //Playerも攻撃対象とかの抽象クラスにするかもね。
    void actionRemoved(Player* player);
    Potion();
    ~Potion(void);
};

#endif /* defined(__diablo__Potion__) */
