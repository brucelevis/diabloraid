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

void TouchedPanels::setRemoved(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->setRemoved();
    }
}

void TouchedPanels::push(PanelSprite* panel){
    // 最初の一回だけ登録
    if(this->containsObject((CCObject*) panel)){
        return;
    }
    
    this->addObject(panel);
}

PanelSprite* TouchedPanels::popTo(PanelSprite *panel){
    if(this->lastObject() == panel){
            return NULL;
        }
    if(!this->containsObject(panel)){
            return NULL;
        }
    int index = this->indexOfObject((CCObject*) panel);
    int lastCount = this->count() - 1;
    for(int i = lastCount; i > index; i--){
            this->removeObjectAtIndex(i);
        }
    return (PanelSprite*) this->objectAtIndex(index);
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