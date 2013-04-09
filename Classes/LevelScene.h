#ifndef __LEVELSCENE_SCENE_H__
#define __LEVELSCENE_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class LevelScene : public cocos2d::CCLayer
{
protected:
    CCTMXTiledMap *_tileMap;
    CCTMXLayer *_background;
    CCTMXLayer *_meta;
    CCSprite *_player;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(LevelScene);
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    CCPoint tileCoordForPosition(CCPoint position);
    CCPoint tileCoordinateFromPos(CCPoint pos);
    void setViewPointCenter(CCPoint position); //以玩家为中心
    void setPlayerPosition(CCPoint position);
    float mapX, mapY;
};


#endif // __HELLOWORLD_SCENE_H__
