//
//  Events.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#ifndef __diablo__Events__
#define __diablo__Events__

#include <iostream>
#include "cocos2d.h"
#include "EventBase.h"
using namespace cocos2d;

class EventBase;
class Events : public CCArray{
public:
    void handle(CCLayer* layer);
};

#endif /* defined(__diablo__Events__) */
