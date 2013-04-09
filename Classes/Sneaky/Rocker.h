//
//  Rocker.h
//  xiyouji
//
//  Created by weng xiangxun on 13-4-8.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//
#ifndef __Rocker.h_H__
#define __Rocker.h_H__

#include "cocos2d.h"
using namespace cocos2d;
class Rocker : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    //触摸相关的处理函数
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void moveing(float dt);//移动逻辑
    
private:
    CCPoint centre;
    CCSprite *yg2;//摇杆小圆圈,在类中创建是因为其他函数还会用到,不像背景只需要初始化加载就行
    float radius;
    
    //精灵相关
    CCSprite * jl;
    float speedX;
    float speedY;
    bool isMove;
    
    CREATE_FUNC(Rocker);
    float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3);
    bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py);
};


#endif // __Rocker.h_H__