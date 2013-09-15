//
//  Stair.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/12.
//
//

#ifndef __diablo__Stair__
#define __diablo__Stair__

#include <iostream>
#include "PanelSprite.h"

class Stair : public PanelSprite{
    int _canExistNum;
public:
    static Stair* createWithSpriteFrameName(const char *pszSpriteFrameName);
    bool canBeAdded(int num);
    Stair();
    ~Stair(void);
};
#endif /* defined(__diablo__Stair__) */
