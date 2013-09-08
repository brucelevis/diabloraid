//
//  MenuScene.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/09/07.
//
//

#include "MenuScene.h"
#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
using namespace CocosDenshion;
using namespace cocos2d;

CCScene* MenuScene::scene(){
    CCLog("MainScene scene");
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = (MenuScene*) MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    CCLog("MainScene init");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    SimpleAudioEngine::sharedEngine()->preloadEffect("ya_01.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("mouhitoiki_01.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("oyasuminasai_03.wav");
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // create menu, it's an autorelease object
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //gameMainLabel = CCLabelTTF::create("GameMain", "Arial", 20);
    //gameMainLabel->setPosition(ccp(size.width/2, size.height/2));
    //this->addChild(gameMainLabel, 1);
    
    CCMenuItemFont *backButton = CCMenuItemFont::itemWithString("GameMain", this, menu_selector(MenuScene::gameMainAction));
    
    CCMenu *menu = CCMenu::menuWithItems(backButton, NULL);
    menu->setPosition(ccp(size.width/2, size.height/2));
    
    this->addChild(menu, 2);
    
    return true;
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    // add "MenuScene" splash screen"
    //CCSprite* pSprite = CCSprite::create("panels.png");
    
    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(MenuScene::update));
    return true;
}
void MenuScene::gameMainAction(){
    SimpleAudioEngine::sharedEngine()->playEffect("ya_01.wav");
    //切り替え先のシーン
    CCScene *scene = MainGameScene::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void MenuScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            CCLog("touch");
            if(gameMainLabel->boundingBox().containsPoint(tap)){
                CCLog("on tap");
            }
        }
    }
}
