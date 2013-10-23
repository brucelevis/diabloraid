//  ModelInstanceManager.cpp
//  model
//
//  Created by Kosuke Takami on 2013/10/20.
//  Copyright (c) 2013年 Kosuke Takami. All rights reserved.
//

#include "ModelInstanceManager.h"

ModelInstanceManager::ModelInstanceManager(){
    name = "ModelInstanceManager";
}
ModelInstanceManager::~ModelInstanceManager(){
}

std::string ModelInstanceManager::getModelName(){
    return name;
}