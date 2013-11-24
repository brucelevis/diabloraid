//
//  LogEvent.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/25.
//
//

#ifndef __diablo__LogEvent__
#define __diablo__LogEvent__

#include <iostream>
#include "EventBase.h"
#include "Events.h"
#include "cocos2d.h"
#include "LogLayer.h"

using namespace cocos2d;

class LogEvent : public EventBase {
    std::string text;
public:
    virtual void action(Events* events, CCLayer* layer);
    void onEnd(); //callbackが呼ばれる直前に呼ばれる。
    LogEvent(std::string text);
    ~LogEvent();
};
#endif /* defined(__diablo__LogEvent__) */
