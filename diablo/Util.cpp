//
//  Util.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/14.
//
//

#include "Util.h"
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

picojson::value Util::JsonParser::parse(const char* path){
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path);
    unsigned long* pFileSize =  (unsigned long*) malloc(sizeof(unsigned long));
    unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", pFileSize);
    picojson::value v;
    
    std::string err;
    picojson::parse(v, pData, pData + strlen((const char*) pData) , &err);
    if(err.empty()){
        return v;
    } else {
        CCLog("err:%s", err.c_str());
    }
    return v;
}

std::string Util::Util::intToString(int i){
    std::ostringstream s;
    s << i;
    const std::string i_as_string(s.str());
    return i_as_string;
}
