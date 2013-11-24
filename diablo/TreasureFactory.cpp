//
//  TreasureFactory.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/24.
//
//

#include "TreasureFactory.h"


UserItem* TreasureFactory::createTreasure(){
    map<string, string> entity = ItemMapMaster::getItem();
    int type   = atoi(entity["type"].c_str());
    int itemId  = atoi(entity["itemId"].c_str());
    
    UserItem* userItem = UserItem::createWithTypeAndItemId(type, itemId);
    return userItem;
}