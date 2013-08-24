#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PanelSprite.h"
#include "Field.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
    Field *_field;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__