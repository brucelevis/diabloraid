//
//  DetailBase.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/17.
//
//

#ifndef __diablo__DetailBase__
#define __diablo__DetailBase__

#include <iostream>
#include "cocos2d.h"
#include "DetailInterface.h"

using namespace cocos2d;

class DetailBase : public CCNode, public DetailInterface {
public:
    static DetailBase* create();
    virtual void addWindowObjects();
    virtual void update();
    DetailBase();
    ~DetailBase();
};

#endif /* defined(__diablo__DetailBase__) */
