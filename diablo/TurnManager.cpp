//
//  TurnManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#include "TurnManager.h"
#include "Enemy.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

TurnManager::TurnManager(Field *field, Player* player){
    _field = field;
    _player = player;
    _turn = 0;
}

TurnManager::~TurnManager(void){
}

int TurnManager::getTurn(){
    return *_turn;
}

void TurnManager::start(){
    CCArray* removedPanels = _field->getWillBeRemovedPanel();
    // 取り除かれたパネルのアクションを実行する。
    this->actionRemoved(removedPanels);
    // パネルをとリ除く
    _field->removePanels();
    CCArray* enemies = _field->getEnemies();
    // パネルを補充
    _field->restockPanels();
    // パネルを移動
    _field->setMoves();
    // 敵の攻撃
    this->attack(enemies);
    // playerの生死を確認
    if(!_player->isAlive()){
        this->gameOver();
    } else {
        _field->onTurnEnd();
        SimpleAudioEngine::sharedEngine()->playEffect("mouhitoiki_01.wav");
    }
    // playerの攻撃状態を解除する。
    _player->resetDamage();
}

void TurnManager::gameOver(){
    SimpleAudioEngine::sharedEngine()->playEffect("gameover.wav");
    //切り替え先のシーン
    CCScene *scene = MenuScene::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
    
}

void TurnManager::actionRemoved(CCArray* removedPanels){
    PanelSprite* panel;
    CCObject* targetObject;
    CCARRAY_FOREACH(removedPanels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->actionRemoved(_player);//player以外にアクションする場合は後で考える。
    }
    
}

void TurnManager::attack(CCArray* enemies){
    Enemy* enemy;
    CCObject* targetObject;
    CCARRAY_FOREACH(enemies, targetObject){
        enemy = (Enemy*) targetObject;
        enemy->attack(_player);
    }
}

void TurnManager::end(){
    _turn++;
}