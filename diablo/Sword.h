//
//  Sword.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__Sword__
#define __diablo__Sword__

#include <iostream>
#include "PanelSprite.h"

class Sword : public PanelSprite{
    int damageValue;
public:
    static Sword* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void actionTouched(Player* player);
    void actionUntouched(Player* player);
    Sword();
    ~Sword(void);
};

#endif /* defined(__diablo__Sword__) */
