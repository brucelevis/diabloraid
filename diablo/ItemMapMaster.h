//
//  ItemMapMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/24.
//
//

#ifndef __diablo__ItemMapMaster__
#define __diablo__ItemMapMaster__

#include <iostream>
#include "Util.h"
#include <map>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ItemMapMaster {
public:
    static map<string, string> getItem(); //確率抽選で落ちたアイテムを取得する
};

#endif /* defined(__diablo__ItemMapMaster__) */