//
//  BagLayer.h
//  diablo
//
//  Created by Kosuke Takami on 2013/10/02.
//
//

#ifndef __diablo__BagLayer__
#define __diablo__BagLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "DetailLayer.h"
#include "UserItems.h"
#include "UserItem.h"
#include "Player.h"
using namespace cocos2d;
using namespace cocos2d::extension;


class BagLayer : public CCLayer,
public CCTableViewDataSource,
public CCTableViewDelegate
{
    Player* player;
    UserItems* userItem;
    int CELL_HEIGHT = 60;
    CCMenuItemSprite* pOkButton;
    CCScene* _scene;
    CCTableView* tableView;
public:
    virtual bool init();
    static CCScene* scene();
    static BagLayer* layer();
    static BagLayer* layerWithUserItemsAndPlayer(UserItems* userItems, Player* player);
    
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
    
    CREATE_FUNC(BagLayer);
};

#endif /* defined(__diablo__BagLayer__) */
