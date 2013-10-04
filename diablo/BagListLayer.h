//
//  BagListLayer.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#ifndef __diablo__BagListLayer__
#define __diablo__BagListLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Equipment.h"
#include "DetailLayer.h"
using namespace cocos2d;
using namespace cocos2d::extension;


class BagListLayer : public CCLayer,
public CCTableViewDataSource,
public CCTableViewDelegate
{
    CCArray* equipmentList;
    int CELL_HEIGHT = 60;
    CCMenuItemSprite* pOkButton;
    CCScene* _scene;
    CCTableView* tableView;
public:
    virtual bool init();
    static CCScene* scene();
    static BagListLayer* layer();
    static BagListLayer* layerWithEquipmentList(CCArray* EquipmentList);
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    virtual CCSize cellSizeForTable(CCTableView* table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView* table);
    
    virtual void scrollViewDidScroll(CCScrollView* view){};
    virtual void scrollViewDidZoom(CCScrollView* view){};
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
    void setScene(CCScene* scene);
    CCScene* getScene();
    
    void addWindowObjects();
    int getTableViewHeight();
    
    void close();
    void update();
    
    CREATE_FUNC(BagListLayer);
};

#endif /* defined(__diablo__BagListLayer__) */
