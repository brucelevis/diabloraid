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

using namespace cocos2d;

class FieldModel : public CCDictionary{
    int WIDTH  = 5; //Fieldの横幅
    int HEIGHT = 5; //Fieldの縦幅
public:
    static FieldModel* create();
    static CCString* convertToPanelName(int panelType);
    static int convertToPanelType(std::string panelName);
    int get(int x, int y);
    CCString* getPanelName(int x, int y);
    void set(int x, int y, int panelType);
    void setMockData();
    FieldModel();
    ~FieldModel();
};

#endif /* defined(__diablo__FieldModel__) */