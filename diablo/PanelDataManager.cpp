//
//  PanelDataManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/20.
//
//

#include "PanelDataManager.h"

// fileから読むなり、なんなりするとしてもこのクラスで行う。
PanelDataManager::PanelDataManager(){
    CCLOG("PanelDataManager constructor");
    _modelMap = new map<string, PanelData*>();
    name = "PanelData";
}

PanelDataManager::~PanelDataManager(){
}

void PanelDataManager::add(PanelData* panelData){
    std::string key = Util::Util::intToString(panelData->getId());
    (*_modelMap)[key] = panelData;
}

void PanelDataManager::remove(PanelData* panelData){
    std::string key = Util::Util::intToString(panelData->getId());
    (*_modelMap)[key] = NULL;
}

PanelData* PanelDataManager::getByPrimaryKey(int id){
    std::string key = Util::Util::intToString(id);
    return (*_modelMap)[key];
}

std::string PanelDataManager::getModelName(){
    return name;
}