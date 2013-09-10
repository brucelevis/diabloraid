//
//  TouchedPanels.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/08.
//
//

#include "TouchedPanels.h"
#include "PanelSprite.h"
#include "cocos2d.h"
using namespace cocos2d;

void TouchedPanels::setRemoved(Player* player){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->setRemoved(player);
    }
}

void TouchedPanels::initialize(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->initialize();
    }
}

// タッチに登録
// やること：[敵1剣1敵2敵3剣2敵4]だったら、
// 剣1に来たら、敵1にダメージ追加
// 敵2に来たら、剣1の分ダメージ追加
// 敵3に来たら、剣1の分ダメージ追加
// 剣2に来たら、敵1、敵2、敵3に剣2の分のダメージ追加
// 敵4に来たら、剣1と剣2の分のダメージ追加
void TouchedPanels::push(PanelSprite* panel, Player* player){
    // 最初の一回だけ登録
    if(this->containsObject((CCObject*) panel)){
        return;
    }
    PanelSprite* p = NULL;
    CCObject* targetObject = NULL;
    panel->actionTouched(player);
    CCARRAY_FOREACH(this, targetObject){
        p = (PanelSprite*) targetObject;
        p->actionTouched(player); //個々までの部分も再実行
    }
    
    
    this->addObject(panel);
}

//タッチから削除
void TouchedPanels::pop(Player* player){
    PanelSprite* p = NULL;
    CCObject* targetObject = NULL;
    PanelSprite* panel = (PanelSprite*) this->lastObject();
    panel->actionUntouched(player);
    this->removeObject(panel);
    CCARRAY_FOREACH(this, targetObject){
        p = (PanelSprite*) targetObject;
        p->actionTouched(player); //個々までの部分も再実行
    }
}

void TouchedPanels::popTo(PanelSprite *panel, Player* player){
    if(this->lastObject() == panel){
        return;
    }
    if(!this->containsObject(panel)){
        return;
    }
    int index = this->indexOfObject((CCObject*) panel);
    int lastCount = this->count() - 1;
    for(int i = 0; i < lastCount - index; i++){
        this->pop(player);
    }
}

void TouchedPanels::showDirections(){
    //順に消えるパネルを取得して、それに合わせて、CCSpriteを生成して、表示する。
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    PanelSprite* _beforePanel;
    PanelSprite* _currentPanel;
    PanelSprite* _nextPanel;
    
    int lastCount = this->count() - 1;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        
        if(count == 0){
            //スタート地点の時は何もしない。
            _beforePanel = panel;
        } else if(count == 1){
            _currentPanel = panel;
            //スタート地点に画像を出す。
            //スタート地点から今のパネルへの方向を得る。
            int direction = _beforePanel->getDirection(_currentPanel);
            _beforePanel->pushDirectionSprite(CCString::createWithFormat("5%d", direction)->intValue());
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int directionA = panel->getDirection(_beforePanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", directionA)->intValue());
            }
        } else if(count == 2){
            //2のとき
            _nextPanel = panel;
            //一個前の位置に方向を出す。
            int directionA = _currentPanel->getDirection(_beforePanel);
            int directionB = _currentPanel->getDirection(_nextPanel);
            if( directionA < directionB){
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionA, directionB )->intValue());
            } else {
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionB, directionA )->intValue());
            }
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int direction = panel->getDirection(_currentPanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", direction)->intValue());
            }
        } else {
            //2以上のとき
            _beforePanel = _currentPanel;
            _currentPanel = _nextPanel;
            _nextPanel = panel;
            int directionA = _currentPanel->getDirection(_beforePanel);
            int directionB = _currentPanel->getDirection(_nextPanel);
            if( directionA < directionB){
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionA, directionB )->intValue());
            } else {
                _currentPanel->pushDirectionSprite(CCString::createWithFormat("%d%d", directionB, directionA )->intValue());
            }
            if (count == lastCount){
            //最後の時だけ、panelにも表示する。
                int direction = panel->getDirection(_currentPanel);
                panel->pushDirectionSprite(CCString::createWithFormat("%d5", direction)->intValue());
            }
        }
        count++;
    }
}