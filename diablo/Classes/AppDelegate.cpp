//
//  diabloAppDelegate.cpp
//  diablo
//
//  Created by Kosuke Takami on 13/08/17.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainGameScene.h"
#include "MenuScene.h"
#include "CCBReader.h"
#include "BagListLayer.h"
#include "DetailLayer.h"
#include "PlayerStatusLayer.h"

using namespace cocos2d::extension;

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionShowAll);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    //create a scene. it's an autorelease object
    //CCScene*pScene = MainGameScene::scene();
    CCScene* pScene = MenuScene::scene();
    //CCScene* pScene = LevelUpLayer::scene();
    //CCScene* pScene = BagListLayer::scene();
    //CCScene* pScene = DetailLayer::scene();
    //CCScene* pScene = PlayerStatusLayer::scene();
//    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
//    CCNode* node = ccbReader->readNodeGraphFromFile("ui/levelup.ccbi");
//    CCScene* pScene = CCScene::create();
//    if(node != NULL){
//        pScene->addChild(node);
//    }
//    ccbReader->release();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
