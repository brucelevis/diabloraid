//
//  Treasure.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/22.
//
//

#ifndef __diablo__Treasure__
#define __diablo__Treasure__

#include <iostream>
#include "PanelSprite.h"

class Treasure : public PanelSprite{
public:
    static Treasure* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void actionRemoved(Player* player);
    Treasure();
    ~Treasure();
    
};

#endif /* defined(__diablo__Treasure__) */
