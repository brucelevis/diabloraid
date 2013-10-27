//
//  FieldModel.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/12.
//
// フィールドの状態を保持するモデルクラス
// これをもとに、fieldが生成されるイメージ
// x, y, panel_type

#ifndef __diablo__FieldModel__
#define __diablo__FieldModel__

#include <iostream>
#include "cocos2d.h"
#include "EnemyMaster.h"

using namespace cocos2d;

class FieldModel : public CCDictionary{
public:
    static int getWidth();
    static int getHeight();
    static FieldModel* create();
    int get(int x, int y);
    void set(int x, int y, int panelId);
    void setMockData();
    FieldModel();
    ~FieldModel();
};

#endif /* defined(__diablo__FieldModel__) */