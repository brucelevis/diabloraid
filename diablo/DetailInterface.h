//
//  DetailInterface.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/16.
//
//

#ifndef __diablo__DetailInterface__
#define __diablo__DetailInterface__


#include <iostream>
#include "UserItem.h"
#include "Belongings.h"

class DetailInterface {
public:
    virtual void addWindowObjects() = 0;
    virtual void update() = 0;
};

#endif /* defined(__diablo__DetailInterface__) */
