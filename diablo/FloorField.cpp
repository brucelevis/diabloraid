//
//  FloorField.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/26.
//
//

#include "FloorField.h"

FloorFieldModel* FloorField::createInitialFloor(Floor* floor){
    int width  = FloorFieldModel::getWidth();
    int height = FloorFieldModel::getHeight();
    
    FloorFieldModel* floorFieldModel = FloorFieldModel::create();
    floorFieldModel->retain();
    int i, j;
    for(i = 0; i < width; i++){
        for (j = 0; j < height; j++){
            PanelData* panelData = PanelSpriteFactory::createPanelDataWithFloor(floor);
            floorFieldModel->set(i, j, panelData->getId());
        }
    }
    return floorFieldModel;
}
