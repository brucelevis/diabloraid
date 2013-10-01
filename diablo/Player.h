//
//  Player.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/05.
//
//

#ifndef __diablo__Player__
#define __diablo__Player__

#include <iostream>
#include "cocos2d.h"
#include "Level.h"
#include "Attributes.h"
#include "Budget.h"
using namespace cocos2d;

class Player{
    CCArray* accumDamages; //パネルをタッチしている間の累積ダメージを保存する。push popで簡単に処理するため
    Attributes* attributes;
    Level* level;
    Budget* budget;
    int levelUpCount;
public:
    Attributes* getAttributes();
    int getCurrentHp();
    int getMaxHp();
    
    int getShieldCurrentHp();
    int getShieldMaxHp();
    
    int getCurrentLevel();
    int getCurrentExp();
    
    int getPotionRecover();
    
    int getShieldRefill();
    
    int getSwordDamage();
    
    int getStrength();
    int getDefense();
    int getDexterity();
    int getVitality();
    int getBudget();
    
    void addCoin();
    
    void damage(int v);
    void damageToShield(int v);
    
    void recover(int v);
    void recoverAllHp();
    void recoverShield(int v);
    
    bool isAlive();
    void pushDamage(int v);
    void popDamage();
    void resetDamage();
    
    int getTotalDamage(); //今回の累積ダメージを取得する。
    void addExp(int addedExp);
    
    int getLevelUpCount(); //レベルアップしたときに、そのレベルアップした数が返る。
    void resetLevelUpCount(); //状態を取得し終わったら、レベルアップのカウントをリセットする。
    
    // for debug
    static Player* getPlayerMock();
    void setAttributes(Attributes* attributes);
    
    Player();
    ~Player(void);
};
#endif /* defined(__diablo__Player__) */