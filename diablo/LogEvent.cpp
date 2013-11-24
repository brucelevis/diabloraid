//
//  LogEvent.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/25.
//
//

#include "LogEvent.h"


void LogEvent::action(Events* events, CCLayer* layer){
    CCLOG("LogEvent::action");
    LogLayer *logLayer = LogLayer::layerWithText(text);
    //push
    logLayer->setCallback(events, layer);
    layer->addChild(logLayer->getScene());
}

void LogEvent::onEnd(){
}


LogEvent::LogEvent(std::string text){
    this->text = text;
}

LogEvent::~LogEvent(){
}