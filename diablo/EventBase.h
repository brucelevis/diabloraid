//
//  EventBase.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//  イベントのベース
//

#ifndef __diablo__EventBase__
#define __diablo__EventBase__

#include <iostream>
#include "Events.h"
#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;
class Events;

class EventBase : public CCNode{
protected:
    Player* _player;
public:
    //actionは、次のイベント発行のタイミングでevents->handle();を呼ぶように実装するべし。
    virtual void action(Events* events, CCLayer* layer);
    virtual void onEnd();
    EventBase(Player* player);
    EventBase();
    ~EventBase();
};

#endif /* defined(__diablo__EventBase__) */