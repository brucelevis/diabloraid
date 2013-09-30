//
//  StatusUpgrade.h
//  diablo
//
//  Created by Kosuke Takami on 2013/09/30.
//
//

#ifndef __diablo__StatusUpgrade__
#define __diablo__StatusUpgrade__

#include "cocos2d.h"
using namespace cocos2d;

#include <iostream>

#endif /* defined(__diablo__StatusUpgrade__) */

class StatusUpgrade : public CCNode {
    int _current;
    int _currentAddition; //注ぎ込まれたポイント数。
    int _remain; //残りポイント（外から渡される。)
    CCLabelTTF* afterLabel;
public:
    StatusUpgrade();
    ~StatusUpgrade();
    static StatusUpgrade* createStatusLine(std::string name, int current, CCPoint position, int remain);
    void addElements(std::string name, CCPoint position);
    void setRemain(int remain);
    int getCurrentAddition();
    void plus();
    void minus();
    char* getDescription(std::string name);
};