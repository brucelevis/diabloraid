#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PanelSprite.h"
#include "Field.h"

#include <typeinfo>

using namespace cocos2d;
using namespace CocosDenshion;


// int を bool に変換
inline bool IntToBool(int a){ return a != 0; }

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    // add "HelloWorld" splash screen"
    //CCSprite* pSprite = CCSprite::create("panels.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("direction.plist");
    
    _field = new Field((CCLayer*) this);
    CCArray *panels = _field->createInitialField();
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(panels,targetObject){
        panel = (PanelSprite*) targetObject;
        this->addChild(panel);
    }
    
    this->setTouchEnabled(true);
 
    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
    _touching = true;
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            _field->onTouchStart(touch);
        }
    }
}

void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            _field->onTouchMove(touch);
        }
    }
    _field->showDirections();
}

void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
    _touching = false;
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            _field->onTouchEnd(touch);
        }
    }
    _field->removePanels();
    _field->restockPanels();
    _field->setMoves();
    _field->onTurnEnd();
}

void HelloWorld::update(float dt){
    _field->movePanels();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
