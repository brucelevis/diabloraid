//
//  LogLayer.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/25.
//
//

#ifndef __diablo__LogLayer__
#define __diablo__LogLayer__

#include <iostream>
#include "cocos2d.h"
#include "Events.h"

using namespace cocos2d;

class LogLayer : public CCLayer{
    CCScene* _scene;
    Events* _events;
    CCLayer* _parentLayer;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static LogLayer* layer();
    static LogLayer* layerWithText(std::string text);
    static CCScene* scene();
    CCScene* getScene();
    void setCallback(Events* events, CCLayer* layer);
    void close();
    CREATE_FUNC(LogLayer);
};

#endif /* defined(__diablo__LogLayer__) */
