//
//  Coin.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__Coin__
#define __diablo__Coin__

#include <iostream>
#include "PanelSprite.h"

class Coin : public PanelSprite{
    int _recoverNum;
public:
    static Coin* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void actionRemoved(Player* player);
    Coin();
    ~Coin(void);
};

#endif /* defined(__diablo__Coin__) */
