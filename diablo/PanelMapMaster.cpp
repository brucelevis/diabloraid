//
//  PanelMapMaster.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/24.
//
//

#include "PanelMapMaster.h"

int PanelMapMaster::getType(){
    picojson::value _records = Util::JsonParser::parse("master/panel_map.json");
    picojson::array &records = _records.get<picojson::array>();
    
    picojson::array::iterator it;
    int probabilityMax = 0;
    //まずは、全アイテムの出現重み付けを計算する。
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        probabilityMax += record["probability"].get<double>();
    }
    int probability = rand() % probabilityMax + 1;
    
    for(it = records.begin(); it != records.end(); it++){
        picojson::object& record = it->get<picojson::object>();
        if(record["probability"].get<double>() >= probability){
            return record["type"].get<double>();
        }
        probability -= record["probability"].get<double>();
    }
    CCAssert(false, "no item is matched");
}