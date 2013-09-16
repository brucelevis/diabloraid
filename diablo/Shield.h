//
//  Shield.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#ifndef __diablo__Shield__
#define __diablo__Shield__

#include "PanelSprite.h"

class Shield : public PanelSprite{
public:
    static Shield* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void actionRemoved(Player* player);
    Shield();
    ~Shield(void);
};

#endif /* defined(__diablo__Shield__) */
