//
//  PanelData.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/14.
//
//

#include "PanelData.h"
int PanelData::seqId = 1;

int PanelData::getSeqId(){
    return seqId++;
}

PanelData* PanelData::create(int type, int typeInstanceId){
    map<string, string> entity;
    entity["type"]           = Util::Util::intToString(type);
    entity["typeInstanceId"] = Util::Util::intToString(typeInstanceId);
    return new PanelData(entity);
}

PanelData::PanelData(map<string, string> entity){
    id             = PanelData::getSeqId();
    type           = atoi(entity["type"].c_str());
    typeInstanceId = atoi(entity["typeInstanceId"].c_str());
}
