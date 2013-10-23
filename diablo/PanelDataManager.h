//
//  PanelDataManager.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/20.
//
//

#ifndef __diablo__PanelDataManager__
#define __diablo__PanelDataManager__

#include <iostream>
#include "ModelInstanceManager.h"
#include "cocos2d.h"
#include "PanelData.h"
#include "Util.h"
using namespace cocos2d;


class PanelDataManager : public ModelInstanceManager{
private:
    map<string, PanelData*> *_modelMap;
    std::string name;
public:
    PanelDataManager();
    ~PanelDataManager();
    void add(PanelData* panelData);
    void remove(PanelData* panelData);
    std::string getModelName();
    PanelData* getByPrimaryKey(int id);
};

#endif /* defined(__diablo__PanelDataManager__) */
