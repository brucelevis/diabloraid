//
//  EquipmentMasterManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/10.
//
//

#include "EquipmentMasterManager.h"


EquipmentMasterManager::EquipmentMasterManager(){
    name = "EquipmentMaster";
}

EquipmentMasterManager::~EquipmentMasterManager(){
}

ModelInterface* EquipmentMasterManager::getByPrimaryKey(int id){
    std::string key = Util::Util::intToString(id);
    if((*_modelMap)[key]!= NULL){
        return (*_modelMap)[key];
    }
    EquipmentMaster* equipmentMaster = EquipmentMaster::getById(id);
    this->add((ModelInterface*) equipmentMaster);
    return (ModelInterface*) equipmentMaster;
}