//
//  PanelMapMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/24.
//
//

#ifndef __diablo__PanelMapMaster__
#define __diablo__PanelMapMaster__

#include <iostream>
#include "Util.h"
#include <map>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class PanelMapMaster {
public:
    static int getType(); //パネルの出現確率に応じてタイプを返す。
};


#endif /* defined(__diablo__PanelMapMaster__) */
