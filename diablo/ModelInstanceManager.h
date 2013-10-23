//
//  ModelInstanceManager.h
//  model
//
//  Created by Kosuke Takami on 2013/10/20.
//  Copyright (c) 2013年 Kosuke Takami. All rights reserved.
//

#ifndef __model__ModelInstanceManager__
#define __model__ModelInstanceManager__

#include <iostream>
#include <map>
#include "Util.h"
#include <sstream>

using namespace std;

// モデルインスタンス自体と管理クラス
class ModelInstanceManager{
private:
//    //ModelInstanceManager( const ModelInstanceManager& );     //封印
//    //void operator=(const ModelInstanceManager& ); //封印
//    // model managerをつり下げる。
//    void append(ModelBase *model);
//    void remove(ModelBase *model);
protected:
//    map< string, ModelBase* > *_modelMap;
    std::string name;
public:
//    virtual ModelBase* getByPrimaryKey(int id);     //idで絞り込める時はidを渡す。
//    virtual ModelBase* create(int id);              //idから生成する。
    virtual std::string getModelName();
    ModelInstanceManager();
    ~ModelInstanceManager();
};

#endif /* defined(__model__ModelInstanceManager__) */