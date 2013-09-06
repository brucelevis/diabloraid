//
//  TurnManager.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/18.
//
//

#include "TurnManager.h"
#include "Enemy.h"

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
    _field->removePanels();
    CCArray* enemies = _field->getEnemies();
    _field->restockPanels();
    _field->setMoves();
    this->attack(enemies);
    _field->onTurnEnd();
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