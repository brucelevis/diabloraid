//
//  PanelData.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#ifndef __diablo__PanelData__
#define __diablo__PanelData__

#include <iostream>
#include "Util.h"
#include "map"
using namespace std;

class PanelData{
private:
    static int seqId;
    int getSeqId();
    int typeInstanceId;
    int id;
    int type;
public:
    int getId();
    int getType();
    int getTypeInstanceId();
    static PanelData* create(int type, int typeInstanceId);
    PanelData(map<string, string> entity);
    ~PanelData();
};

#endif /* defined(__diablo__PanelData__) */