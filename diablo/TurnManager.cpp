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
    TouchedPanels* removedPanels = _field->getWillBeRemovedPanel();
    //removedPanelsの数が3以下なら表示をもとに戻す以外は何もしない。
    if(removedPanels->count() < 3 && !removedPanels->hasActiveOnlyOnePanel()){
        this->turnEnd();
        return;
    }
    if(removedPanels->hasActiveOnlyOnePanel()){
        _field->removeAllPanels();
        _field->restockPanels();
        _field->setMoves();
        this->turnEnd();
        SimpleAudioEngine::sharedEngine()->playEffect("kaidan.wav");
        return;
    }
    // 取り除かれそうになっているパネルのアクションを実行する。
    this->actionGotoRemoved(removedPanels);
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
        return;
    }
    this->turnEnd();
    
    SimpleAudioEngine::sharedEngine()->playEffect("mouhitoiki_01.wav");
}

void TurnManager::gameOver(){
    SimpleAudioEngine::sharedEngine()->playEffect("oyasuminasai_03.wav");
    //切り替え先のシーン
    CCScene *scene = MenuScene::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
    
}

void TurnManager::turnEnd(){
    _field->initialize();
    _field->onTurnEnd();
    // playerの攻撃状態を解除する。
    _player->resetDamage();
    
}

void TurnManager::actionGotoRemoved(cocos2d::CCArray *removedPanels){
    PanelSprite* panel;
    CCObject* targetObject;
    CCARRAY_FOREACH(removedPanels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->actionGotoRemoved(_player);//player以外にアクションする場合は後で考える。
    }
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