//
//  DialogLayerInterface.h
//  diablo
//
//  Created by Kosuke Takami on 2013/11/19.
//
//

#ifndef __diablo__DialogLayerInterface__
#define __diablo__DialogLayerInterface__

#include <iostream>
class DialogLayerInterface{
public:
    virtual void close() = 0;
    virtual ~DialogLayerInterface(){};
};

#endif /* defined(__diablo__DialogLayerInterface__) */
