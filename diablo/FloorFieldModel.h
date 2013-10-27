//
//  FloorFieldModel.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/27.
//
//

#ifndef __diablo__FloorFieldModel__
#define __diablo__FloorFieldModel__

#include <iostream>
#include "cocos2d.h"
#include "FieldModel.h"
using namespace cocos2d;

//マップ全体のデータ

class FloorFieldModel : public CCDictionary {
public:
    static int getWidth();
    static int getHeight();
    static FloorFieldModel* create();
    int get(int x, int y);
    FieldModel* getByIndex(int x, int y); // x, y から 6 * 6を取得する。
    void set(int x, int y, int panelId);
    void setMockData();
    FloorFieldModel();
    ~FloorFieldModel();
};

#endif /* defined(__diablo__FloorFieldModel__) */