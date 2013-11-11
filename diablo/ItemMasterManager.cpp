//
//  ItemMasterManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/10.
//
//

#include "ItemMasterManager.h"

ItemMasterManager::ItemMasterManager(){
    name = "ItemMaster";
}

ItemMasterManager::~ItemMasterManager(){
}

ModelInterface* ItemMasterManager::getByPrimaryKey(int id){
    std::string key = Util::Util::intToString(id);
    if((*_modelMap)[key]!= NULL){
        return (*_modelMap)[key];
    }
    ItemMaster* itemMaster = ItemMaster::getById(id);
    this->add((ModelInterface*) itemMaster);
    return (ModelInterface*) itemMaster;
}