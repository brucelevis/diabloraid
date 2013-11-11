//
//  HavingMasterInterface.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/09.
//
//

#ifndef __diablo__HavingMasterInterface__
#define __diablo__HavingMasterInterface__

#include <iostream>

class HavingMasterInterface{
public:
    virtual std::string getName() = 0;
    virtual ~HavingMasterInterface(){};
};


#endif /* defined(__diablo__HavingMasterInterface__) */
