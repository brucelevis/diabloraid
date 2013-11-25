//
//  Enemy.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/06.
//
//

#ifndef __diablo__Enemy__
#define __diablo__Enemy__

#include <iostream>
#include "HitPoint.h"
#include "PanelSprite.h"
#include "Player.h"
#include "BaseDamage.h"
#include "ShieldStatus.h"
#include "EnemyMaster.h"
#include "EnemyData.h"
#include "Util.h"

class Enemy : public PanelSprite
{
    int damage;
    Player* player;
    HitPoint* hp;
    BaseDamage* baseDamage; //BaseDamageクラスを一応使う
    ShieldStatus*  shieldStatus;  //ShieldStatusクラスを一応使う
    EnemyMaster* enemyMaster;
    int exp;
    CCLabelTTF* currentHpLabel; //今のhpの表示
    CCLabelTTF* baseDamageLabel;  //攻撃力の表示
    CCLabelTTF* shieldStatusLabel;  //攻撃力の表示
    bool _isEnemy;
    void actionAttack();
    void addAttackLog();
public:
    static Enemy* createWithEnemyMaster(EnemyMaster* enemy);
    static Enemy* createWithEnemyData(EnemyData* enemyData);
    bool isEnemy();
    void attack(Player* player); //Playerも攻撃対象とかの抽象クラスにするかもね。
    void setRemoved(Player* player);
    void actionGotoRemoved(Player* player);
    void actionTouched(Player* player);
    void actionUntouched(Player* player);
    void setKilledImage();
    void update();
    Enemy(EnemyMaster* enemy);
    ~Enemy(void);
};

#endif /* defined(__diablo__Enemy__) */
