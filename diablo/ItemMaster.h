//
//  ItemMaster.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/07.
//
//

#ifndef __diablo__ItemMaster__
#define __diablo__ItemMaster__

#include <iostream>
#include "HavingMasterInterface.h"
#include "ModelInterface.h"
#include "picojson.h"
#include "Util.h"

class ItemMaster : public HavingMasterInterface, public ModelInterface {
    picojson::value _records;
    int _id;
    std::string _name;
    std::string description;
    int type;
    int value;
public:
    static ItemMaster* getById(int v);
    std::string getName();
    std::string getDescription();
    int getId();
    int getType();
    int getValue();
    ItemMaster(int v);
    ~ItemMaster();
};

#endif /* defined(__diablo__ItemMaster__) */
