//
//  LevelMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#ifndef __diablo__LevelMaster__
#define __diablo__LevelMaster__

#include <iostream>
#include "picojson.h"
#include "Util.h"
#include "cocos2d.h"
using namespace cocos2d;

class LevelMaster{
    picojson::value _records;
    int _id;
    int _level;
    int _currentLevelExp;
    int _requiredExp;
public:
    static LevelMaster* getById(int v);
    static int getLevel(int level, int exp);//スピード稼ぐために現在のレベルから検索する。
    
    LevelMaster(int v);
    ~LevelMaster();
};

#endif /* defined(__diablo__LevelMaster__) */