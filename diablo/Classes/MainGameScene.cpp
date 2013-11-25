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
    CCLOG("MainGameScene: touchPriority: %d", this->getTouchPriority());
    //this->setTouchPriority(kCCMenuHandlerPriority);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panels.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("direction.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hp.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("icon_button.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");
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
    CCLOG("pMenu: touchPriority: %d", pMenu->getTouchPriority());
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
       
    CCSprite* statusIcon = CCSprite::createWithSpriteFrameName("status_icon.png");
    CCSprite* statusIconOff = CCSprite::createWithSpriteFrameName("status_icon.png");
    statusIconOff->setColor(ccc3(102,102,102));
    
    CCMenuItemSprite* pStatusButton =
        CCMenuItemSprite::create(statusIcon, statusIconOff, this, menu_selector(MainGameScene::pushStatusScene));
    pStatusButton->setPosition(ccp(20, 460));
    pStatusButton->setScale(0.3);
    
    CCSprite* equipIcon = CCSprite::createWithSpriteFrameName("equiplist_icon.png");
    CCSprite* equipIconOff = CCSprite::createWithSpriteFrameName("equiplist_icon.png");
    equipIconOff->setColor(ccc3(102,102,102));
    
    CCMenuItemSprite* pEquipButton =
        CCMenuItemSprite::create(equipIcon, equipIconOff, this, menu_selector(MainGameScene::pushEquipScene));
    pEquipButton->setPosition(ccp(70, 460));
    pEquipButton->setScale(0.3);
    
    CCSprite* shopIcon = CCSprite::createWithSpriteFrameName("equiplist_icon.png");
    CCSprite* shopIconOff = CCSprite::createWithSpriteFrameName("equiplist_icon.png");
    shopIconOff->setColor(ccc3(102,102,102));
    
    CCMenuItemSprite* pShopButton =
        CCMenuItemSprite::create(shopIcon, shopIconOff, this, menu_selector(MainGameScene::pushShop));
    pShopButton->setPosition(ccp(120, 460));
    pShopButton->setScale(0.3);
    
    CCMenu* pStatus = CCMenu::create(pEquipButton, pStatusButton, pShopButton, NULL);
    pStatus->setPosition(CCPointZero);
    this->addChild(pStatus,1);

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
    
    
    _player = new Player();
    
    CCPoint point = ccp(0, 0);
    _camera = new Camera(point, CCRectMake(0, 97, 305, 305));
    
    Floor* floor = new Floor(1);
    FloorFieldModel* floorFieldModel = FloorFieldModel::create();
    floorFieldModel->retain();
    _field = new Field(_player, _camera, floor, floorFieldModel);
    this->addChild((CCNode*) _field);
    
    _events = (Events*) Events::create();
    _events->retain();
    
    userItem = _player->getUserItem();
    
    CCSprite* _hp = CCSprite::createWithSpriteFrameName("hp.png");
    _hp->setScale(0.4);
    _hp->setPosition(ccp(230, 50));
    this->addChild(_hp);
    
    HpLabel = CCLabelTTF::create(CCString::createWithFormat("%d/%d", _player->getCurrentHp(), _player->getMaxHp())->getCString(), "arial", 20);
    HpLabel->setPosition(ccp(240, 50));
    this->addChild(HpLabel);
    
    ShieldLabel = CCLabelTTF::create(CCString::createWithFormat("%d/%d", _player->getShieldCurrentHp(), _player->getShieldMaxHp())->getCString(), "arial", 20);
    ShieldLabel->setPosition(ccp(140, 70));
    this->addChild(ShieldLabel);
    
    TurnLabel = CCLabelTTF::create(CCString::createWithFormat("Turn:%d", _field->getTurn())->getCString(), "arial", 20);
    TurnLabel->setPosition(ccp(size.width / 2, size.height - 43) );
    this->addChild(TurnLabel);
    
    FloorLabel = CCLabelTTF::create(CCString::createWithFormat("%d F", _field->getFloor())->getCString(), "arial", 20);
    FloorLabel->setPosition(ccp(size.width - 50, size.height - 63) );
    this->addChild(FloorLabel);
    
    levelLabel = CCLabelTTF::create(CCString::createWithFormat("level: %d(%d)", _player->getCurrentLevel(), _player->getCurrentExp())->getCString(), "arial", 20);
    levelLabel->setPosition(ccp(size.width / 2, size.height - 63) );
    this->addChild(levelLabel);
    
    budgetLabel = CCLabelTTF::create(CCString::createWithFormat("coin: %d", _player->getBudget())->getCString(), "arial", 20);
    budgetLabel->setPosition(ccp(size.width -50, size.height - 43));
    this->addChild(budgetLabel);
    
    DamageLabel = CCLabelTTF::create(CCString::createWithFormat("%d DMG", _player->getTotalDamage())->getCString(), "arial", 20);
    DamageLabel->setColor(ccc3(0,255,0));
    DamageLabel->setPosition(ccp(140, 50));
    DamageLabel->setVisible(false);
    this->addChild(DamageLabel,1000);
    
    _turnManager = new TurnManager(this, _field, _player, _camera);
    
    
    this->setTouchEnabled(true);
 
    this->schedule(schedule_selector(MainGameScene::update));
    return true;
}

void MainGameScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
    _touching = true;
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint loc;
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            loc = touch->getLocation();
            _field->onTouchStart(touch);
        }
    }
    if(this->showDamage(_field->getConnectPanel())){
        DamageLabel->setPosition(ccp(loc.x + 20,loc.y + 40));
        DamageLabel->setVisible(true);
    }
}

void MainGameScene::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        CCPoint loc = touch->getLocation();
        DamageLabel->setPosition(ccp(loc.x + 20,loc.y + 40));
        
        if(touch) {
            _field->onTouchMove(touch);
        }
    }
}
bool MainGameScene::showDamage(PanelSprite* panel){
    if(!panel){
        return false;
    }
    return (panel->getConnectType() == 1);
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
    DamageLabel->setVisible(false);
    _turnManager->start();
}

void MainGameScene::update(float dt){
    _field->update();
    _camera->update();
    HpLabel->setString(CCString::createWithFormat("%d/%d", _player->getCurrentHp(), _player->getMaxHp())->getCString());
    DamageLabel->setString(CCString::createWithFormat("%d DMG", _player->getTotalDamage())->getCString());
    ShieldLabel->setString(CCString::createWithFormat("%d/%d", _player->getShieldCurrentHp(), _player->getShieldMaxHp())->getCString());
    TurnLabel->setString(CCString::createWithFormat("Turn:%d", _field->getTurn())->getCString());
    FloorLabel->setString(CCString::createWithFormat("%d F", _field->getFloor())->getCString());
    levelLabel->setString(CCString::createWithFormat("level: %d(%d)", _player->getCurrentLevel(), _player->getCurrentExp())->getCString());
    budgetLabel->setString(CCString::createWithFormat("coin: %d", _player->getBudget())->getCString());
}

void MainGameScene::watchPlayerLevelUp(){
    if(this->_player->getLevelUpCount() == 0){
        return;
    }
    int i;
    int levelUpCount = this->_player->getLevelUpCount();
    CCLOG("levelUpCount%d", levelUpCount);
    for(i = 0; i < levelUpCount; i++){
        CCLOG("levelup");
        this->pushLevelUpEvent();
    }
    this->_player->resetLevelUpCount();
}

void MainGameScene::watchPlayerLog(){
    if(!this->_player->hasPlayerLog()){
        return;
    }
    while(this->_player->hasPlayerLog()){
        std::string text = this->_player->popPlayerLog();
        _events->addObject((CCObject*) new LogEvent(text));
    }
}

void MainGameScene::pushLevelUp(){
}

void MainGameScene::pushEquipScene(){
    BagLayer *bagLayer = BagLayer::layerWithUserItemsAndPlayer(userItem, _player);
    //push
    this->addChild(bagLayer->getScene());
}

void MainGameScene::pushStatusScene(){
    //BagListLayer *bagListLayer = BagListLayer::layerWithEquipmentList(_equipmentList);
    PlayerStatusLayer* playerStatusLayer = PlayerStatusLayer::layerWithPlayer(_player);
    
    //push
    this->addChild(playerStatusLayer->getScene());
}

void MainGameScene::pushLevelUpEvent(){
    _events->addObject((CCObject*) EventFactory::create(1, _player));
}

void MainGameScene::pushShop(){
    CCLOG("pushShop");
    LogLayer *logLayer = LogLayer::layer();
    //push
    this->addChild(logLayer->getScene());
}

void MainGameScene::handleEvents(){
    CCLOG("MainGameScene::handleEvents:%d", _events->count());
    _events->handle(this);
}

void MainGameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
