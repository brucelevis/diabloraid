//
//  Util.h
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#ifndef __diablo__Util__
#define __diablo__Util__

#include <iostream>
#include "picojson.h"

namespace Util {
    class JsonParser{
    public:
        static picojson::value parse(const char* path);
    };
};

#endif /* defined(__diablo__Util__) */
