#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "ShunSprite.h"
using namespace cocos2d;
using namespace CocosDenshion;

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

    _tileMap = CCTMXTiledMap::create("map.tmx");
    _background = _tileMap->layerNamed("Background");

    this->addChild(_tileMap,-1);
    
    CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("object");
    CCDictionary *c = objects->objectNamed("SpawnPoint");
   
    
    CCTMXObjectGroup *group = _tileMap->objectGroupNamed("object");
    CCDictionary *spwnPoint = group->objectNamed("SpawnPoint");
    int px = spwnPoint->valueForKey("x")->floatValue();
    int py = spwnPoint->valueForKey("y")->floatValue();
    
    
    
    _player = ShunSprite::create();
    _player->setPosition(ccp(px,py));
    _tileMap->addChild(_player);
    this->setViewPointCenter(_player->getPosition());
//    CCTMXLayer *wall = _tileMap->layerNamed("wall");
//    wall->setVisible(false);
    _meta = _tileMap->layerNamed("meta");
    _meta->setVisible(false);
    

    
    int gid = _background->tileGIDAt(ccp(10,10));
    CCLog("backGID:%d",gid);
    
    this->registerWithTouchDispatcher();
    return true;
}

CCPoint HelloWorld::tileCoordForPosition(cocos2d::CCPoint position){

//    int x = position.x / _tileMap.tileSize.width
    int x = position.x / _tileMap->getTileSize().width;
    
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position. y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

void HelloWorld::setViewPointCenter(cocos2d::CCPoint position){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, _tileMap->getMapSize().width*_tileMap->getTileSize().width- winSize.width/2);
    y = MIN(y, _tileMap->getMapSize().height*_tileMap->getTileSize().height- winSize.height/2);
    
    CCPoint actualPoint = ccp(x,y);
    CCPoint centerOfview = ccp(winSize.width/2,winSize.height/2);
    
    CCPoint viewPoint = ccpSub(centerOfview, actualPoint);
    CCLog("%f---%f",position.x,position.y);
    CCLog("%f---%f",actualPoint.x,actualPoint.y);
    CCLog("%f---%f",centerOfview.x,centerOfview.y);
    CCLog("%f---%f",viewPoint.x,viewPoint.y);
    this->setPosition(viewPoint);
}

void HelloWorld::setPlayerPosition(cocos2d::CCPoint position){
    CCPoint tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->tileGIDAt(tileCoord);//[_meta tileGIDAt:tileCoord];
    
    if (tileGid) {
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);//[_tileMap propertiesForGID:tileGid];
        CCLog("%s",properties);
        
        if (properties) {
           const CCString *collision = properties->valueForKey("Collidable");//[properties valueForKey:@"Collidable"];
            CCLog("%s",collision->getCString());
            CCLog("%d",collision->compare("wxx"));
            if (collision && collision->compare("wxx") == 0) { return;
            }
        }
    }
//    _player.position = position;
    _player->setPosition(position);
}

void HelloWorld::registerWithTouchDispatcher(){
    
    //    CCTouchDispatcher::addStandardDelegate(self, 0);
    //    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    //    pDispatcher->setPriority(newPriority, this);
    //    CCDirector* pDirector = CCDirector::sharedDirector();
    //    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //    CCPoint touchLocation = pTouch->locationInView(pTouch->view());
//    CCPoint touchP = pTouch->getLocationInView();
//    CCPoint prevP = pTouch->getPreviousLocationInView();
//    
//    touchP = CCDirector::sharedDirector()->convertToGL(touchP);
//    prevP = CCDirector::sharedDirector()->convertToGL(prevP);
//    CCLog("touchPx:%f  y:%f   prevPx:%f   y:%f",touchP.x,touchP.y,prevP.x,prevP.y);
//    CCPoint diff = ccpSub(touchP, prevP);
//    CCNode* node = getChildByTag(tagTileMap);
//    CCPoint currentP = node->getPosition();
//    node->setPosition(ccpAdd(currentP, diff));
}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCPoint location = pTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCActionInterval *action = CCMoveTo::create(3, location);
//    _player->runAction(action);
    this->setPlayerPosition(location);
    this->setViewPointCenter(_player->getPosition());
    
    _background->setTileGID(10, ccp(6,37));
}

void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
