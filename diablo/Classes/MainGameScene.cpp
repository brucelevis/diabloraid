#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "PanelSprite.h"
#include "Field.h"

#include <typeinfo>

using namespace cocos2d;
using namespace CocosDenshion;


// int を bool に変換
inline bool IntToBool(int a){ return a != 0; }

CCScene* MainGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainGameScene *layer = MainGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
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
                                        menu_selector(MainGameScene::menuCloseCallback) );
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
    // add "MainGameScene" splash screen"
    //CCSprite* pSprite = CCSprite::create("panels.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("direction.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hp.plist");
    
    
    _player = new Player();
    _field = new Field((CCLayer*) this, _player);
    CCArray *panels = _field->createInitialField();
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    CCSprite* _hp = CCSprite::createWithSpriteFrameName("hp.png");
    _hp->setScale(0.4);
    _hp->setPosition(ccp(230, 50));
    this->addChild(_hp);
    
    HpLabel = CCLabelTTF::create(CCString::createWithFormat("%d/%d", _player->hp->getCurrentHp(), _player->hp->getMaxHp())->getCString(), "arial", 20);
    HpLabel->setPosition(ccp(240, 50));
    this->addChild(HpLabel);
    
    DamageLabel = CCLabelTTF::create(CCString::createWithFormat("%d", _player->getTotalDamage())->getCString(), "arial", 20);
    DamageLabel->setPosition(ccp(140, 50));
    this->addChild(DamageLabel);
    
    _turnManager = new TurnManager(_field, _player);
    
    CCARRAY_FOREACH(panels,targetObject){
        panel = (PanelSprite*) targetObject;
        this->addChild(panel);
    }
    
    this->setTouchEnabled(true);
 
    this->schedule(schedule_selector(MainGameScene::update));
    return true;
}

void MainGameScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
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

void MainGameScene::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            _field->onTouchMove(touch);
        }
    }
}

void MainGameScene::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
    _touching = false;
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            _field->onTouchEnd(touch);
        }
    }
    _turnManager->start();
}

void MainGameScene::update(float dt){
    _field->movePanels();
    _field->cleanUp();
    _field->showDirections();
    HpLabel->setString(CCString::createWithFormat("%d/%d", _player->hp->getCurrentHp(), _player->hp->getMaxHp())->getCString());
    DamageLabel->setString(CCString::createWithFormat("%d", _player->getTotalDamage())->getCString());
}

void MainGameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
