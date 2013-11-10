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
#include "PanelData.h"
#include "cocos2d.h"
#include "Util.h"
using namespace cocos2d;


class PanelDataManager : public ModelInstanceManager{
private:
public:
    PanelDataManager();
    ~PanelDataManager();
};

#endif /* defined(__diablo__PanelDataManager__) */
