//
//  Floor.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/13.
//
//

#ifndef __diablo__Floor__
#define __diablo__Floor__

#include <iostream>

class Floor{
    int current; //
public:
    void up(int v);// vだけ上る。
    Floor(int v);
    ~Floor();
};

#endif /* defined(__diablo__Floor__) */
