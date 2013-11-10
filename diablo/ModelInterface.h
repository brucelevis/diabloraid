//
//  ModelInterface.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/10.
//
//

#ifndef __diablo__ModelInterface__
#define __diablo__ModelInterface__

#include <iostream>
class ModelInterface{
public:
    virtual int getId() = 0;
    virtual ~ModelInterface(){};
};

#endif /* defined(__diablo__ModelInterface__) */
