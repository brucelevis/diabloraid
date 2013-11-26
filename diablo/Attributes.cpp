//
//  Attributes.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/10/01.
//
//

#include "Attributes.h"

Attributes::Attributes(){
}

Attributes::~Attributes(){
}

Attributes* Attributes::createWithCCDictionary(CCDictionary* dictionary){
    int _bd = ((CCInteger*) dictionary->objectForKey("baseDamage"))->getValue();
    int _hp= ((CCInteger*) dictionary->objectForKey("hp"))->getValue();
    int _sd = ((CCInteger*) dictionary->objectForKey("swordDamage"))->getValue();;
    int _pr = ((CCInteger*) dictionary->objectForKey("potionRecover"))->getValue();
    int _ss = ((CCInteger*) dictionary->objectForKey("shieldStatus"))->getValue();
    int _sr = ((CCInteger*) dictionary->objectForKey("shieldRefill"))->getValue();
    int _ca = ((CCInteger*) dictionary->objectForKey("coinAddition"))->getValue();
    int _str  = ((CCInteger*) dictionary->objectForKey("strength"))->getValue();
    int _def  = ((CCInteger*) dictionary->objectForKey("defense"))->getValue();
    int _dex  = ((CCInteger*) dictionary->objectForKey("dexterity"))->getValue();
    int _vit  = ((CCInteger*) dictionary->objectForKey("vitality"))->getValue();
    int _hungryP = ((CCInteger*) dictionary->objectForKey("hungryP"))->getValue();
    
    return _create(_hp, _ss, _bd, _sd, _pr, _sr, _ca, _str, _def, _vit, _dex, _hungryP);
}

Attributes* Attributes::createWithDefault(){
    return _create(50, 5, 5, 5, 0, 2, 5, 5, 5, 5, 3, 100);
}

Attributes* Attributes::_create(int _hp, int _ss, int _bd, int _sd, int _pr, int _sr, int _ca, int _str, int _def, int _vit, int _dex, int _hungryP){
    Attributes* attr = new Attributes();
    attr->hp            = new HitPoint(_hp); //base hp
    attr->vitality      = new Vitality(_vit);
    attr->hp->increaseMaxHp(attr->vitality->getCalculatedHp(attr->vitality->getCurrent()));
    attr->hp->recoverAll();
    
    attr->shieldRefill  = new ShieldRefill(_sr);
    attr->shieldStatus  = new ShieldStatus(_ss);  //shieldStatus
    attr->defense       = new AttributeBase(_def);
    attr->shieldStatus->increaseMaxHp(attr->defense->getCurrent());
    
    attr->baseDamage    = new BaseDamage(_bd);
    attr->swordDamage   = new SwordDamage(_sd);
    attr->potionRecover = new PotionRecover(_pr);
    attr->strength      = new AttributeBase(_str);
    attr->dexterity     = new AttributeBase(_dex);
    attr->coinAddition   = new AttributeBase(_ca);
    attr->hungryP       = new HungryPoint(_hungryP);
    return attr;
}



int Attributes::getStrength(){
    return strength->getCurrent();
}

int Attributes::getDefense(){
    return defense->getCurrent();
}

int Attributes::getVitality(){
    return vitality->getCurrent();
}

int Attributes::getDexterity(){
    return dexterity->getCurrent();
}


int Attributes::getSwordDamage(){
    return this->swordDamage->getDamage() + this->strength->getCurrent();
}

int Attributes::getPotionRecover(){
    return this->potionRecover->getValue() + dexterity->getCurrent();
}

int Attributes::getShieldRefill(){
    return this->shieldRefill->getValue();
}

int Attributes::getCurrentHp(){
    return this->hp->getCurrentHp();
}

int Attributes::getMaxHp(){
    return this->hp->getMaxHp();
}

int Attributes::getShieldCurrentHp(){
    return this->shieldStatus->getCurrent();
}

int Attributes::getShieldMaxHp(){
    return this->shieldStatus->getMax();
}

int Attributes::getBaseDamage(){
    return this->baseDamage->getValue();
}

int Attributes::getCoinAddition(){
    return this->coinAddition->getCurrent();
}

// ダメージを受けたらhpを減らす。
void Attributes::damage(int v){
    hp->reduce(v);
}
// シールドにダメージを与える。
void Attributes::damageToShield(int v){
    this->shieldStatus->damage(v);
}

//回復したらhpを増やす。
void Attributes::recover(int v){
    hp->increase(v);
}

void Attributes::recoverAllHp(){
    hp->recoverAll();
}

//シールドのhpを回復する。
void Attributes::recoverShield(int v){
    shieldStatus->increase(v);
}

bool Attributes::isAlive(){
    return hp->getCurrentHp() > 0;
}

void Attributes::addStrength(int v){
    strength->add(v);
}

void Attributes::addDefense(int v){
    defense->add(v);
    shieldStatus->increaseMaxHp(v);
}

void Attributes::addDexterity(int v){
    dexterity->add(v);
}

void Attributes::addVitality(int v){
    vitality->add(v);
    hp->increaseMaxHp(vitality->getCalculatedHp(v)); //上昇させる。
}

Attributes* Attributes::getAttributesMock(){
    return createWithDefault();
}
