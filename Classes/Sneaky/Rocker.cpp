//
//  Rocker.cpp
//  xiyouji
//
//  Created by weng xiangxun on 13-4-8.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//
 
#include "Rocker.h"
//
//using namespace cocos2d;

CCScene* Rocker::scene()
{
    CCScene *scene = CCScene::create();
    Rocker *layer = Rocker::create();
    scene->addChild(layer);
    return scene;
}

// 初始化
bool Rocker::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        CCSize s = CCDirector::sharedDirector()->getWinSize();//获得屏幕大小，保持到s中
        
        CCSprite *yg1 = CCSprite::create("yg1.png");//加载摇杆背景图
        yg1->setOpacity(190);                        //设置透明度
        yg1->setAnchorPoint(ccp(0,0));               //设置锚点位置
        yg1->setPosition(ccp(0,0));                  //设置显示位置
        radius = yg1->getContentSize().width/2;      //计算半径
        centre = ccp(radius,radius);                //计算中心
        this->addChild(yg1,1);                       //添加到场景中
        
        yg2 = CCSprite::create("yg2.png");//加载摇杆小圈
        yg2->setPosition(ccp(centre.x, centre.y));
        this->addChild(yg2,2);
        
        jl = CCSprite::create("jl.png");//加载需要被控制的图片...叫精灵好听一些
        CC_BREAK_IF(!jl);
        jl->setPosition(ccp(s.width/2, s.height/2));
        this->addChild(jl,1);
        
        
        this->setTouchEnabled(true);               //开启触摸,不开的话点击屏幕是没用的
        this->schedule(schedule_selector(Rocker::moveing));//这句理解为开启逻辑吧,这里的逻辑是处理精灵的移动
        bRet = true;
    } while (0);
    
    return bRet;
}

//触摸开始..也就是点击屏幕
void Rocker::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();
    CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);
    
    CCRect rect=yg2->boundingBox();
    
    if (rect.containsPoint(convertedLocation))//判断触摸的范围。如果是在摇杆内的话，才响应
    {
        isMove=true;
    }
    CCLog("开始触摸");
}

//触摸移动的处理...也就是按下后再移动
void Rocker::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();
    CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);
    CCLog("一直触摸");
    bool inRange=pow(centre.x-convertedLocation.x,2)+pow(centre.y-convertedLocation.y,2)<pow(radius,2);
//    CCLog("");
    if (isMove) {
        CCLog("touch");
    }
    if (inRange) {
        CCLog("inrange");
    }
    if(isMove&&inRange)
    {
        CCPoint position=jl->getPosition();
        yg2->setPosition(convertedLocation);
        
        float radius1=radius*2/6;//十字键中心区的内切圆半径
        float side=radius*2/3;//九宫格中一个格子的边长
        
        //我们使用海伦公式来计算面积，进而判断十字键中心区的精确方向
        //向上
        if(triangleContainPoint(centre.x,centre.y,centre.x-radius1,centre.y+radius1,centre.x+radius1,centre.y+radius1,convertedLocation.x,convertedLocation.y)
           ||CCRectMake(centre.x-radius1,centre.y+radius1,side,side).containsPoint(convertedLocation))
        {
            speedX=0;
            speedY=1;
        }
        //向下
        else if(triangleContainPoint(centre.x,centre.y,centre.x-radius1,centre.y-radius1,centre.x+radius1,centre.y-radius1,convertedLocation.x,convertedLocation.y)
                ||CCRectMake(centre.x-radius1,centre.y-radius1-side,side,side).containsPoint(convertedLocation))
        {
            speedX=0;
            speedY=-1;
        }
        //向左
        else if(triangleContainPoint(centre.x,centre.y,centre.x-radius1,centre.y+radius1,centre.x-radius1,centre.y-radius1,convertedLocation.x,convertedLocation.y)
                ||CCRectMake(centre.x-radius1-side,centre.y-radius1,side,side).containsPoint(convertedLocation))
        {
            speedX=-1;
            speedY=0;
        }
        //向右
        else if (triangleContainPoint(centre.x,centre.y,centre.x+radius1,centre.y+radius1,centre.x+radius1,centre.y-radius1,convertedLocation.x,convertedLocation.y)
                 ||CCRectMake(centre.x+radius1+side,centre.y-radius1,side,side).containsPoint(convertedLocation))
        {
            speedX=1;
            speedY=0;
        }
//        //右上
//        else if(convertedLocation.x-centre.x>0&&convertedLocation.y-centre.y>0)
//        {
//            speedX=0.7f;
//            speedY=0.7f;
//        }
//        //左上
//        else if (convertedLocation.x-centre.x<0&&convertedLocation.y-centre.y>0)
//        {
//            speedX=-0.7f;
//            speedY=0.7f;
//        }
//        //左下
//        else if (convertedLocation.x-centre.x<0&&convertedLocation.y-centre.y<0)
//        {
//            speedX=-0.7f;
//            speedY=-0.7f;
//        }
//        //右下
//        else if (convertedLocation.x-centre.x>0&&convertedLocation.y-centre.y<0)
//        {
//            speedX=0.7f;
//            speedY=-0.7f;
//        }
    }
}

//海伦公式
float Rocker::heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
{
    float a=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    float b=sqrt(pow(x2-x3,2)+pow(y2-y3,2));
    float c=sqrt(pow(x3-x1,2)+pow(y3-y1,2));
    float s=(a+b+c)/2;
    
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool Rocker::triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)
{
    float s1=heronsformula(x1,y1,x2,y2,px,py);
    float s2=heronsformula(x2,y2,x3,y3,px,py);
    float s3=heronsformula(x3,y3,x1,y1,px,py);
    float s=heronsformula(x1,y1,x2,y2,x3,y3);
    
    return abs(s-(s1+s2+s3))<0.001f;
}


//触摸结束..也就是松开后的处理
void Rocker::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    isMove=false;            //关闭移动逻辑
    yg2->setPosition(centre);//把摇杆小圈初始化为中心
    speedX=speedY=0;
        CCLog("结束触摸");
}

//移动逻辑的处理函数
void Rocker::moveing(float dt)
{
    if (isMove&&(speedX!=0||speedY!=0))
    {
        CCPoint position=ccp(jl->getPosition().x+speedX,jl->getPosition().y+speedY);
        
        CCSize size=CCDirector::sharedDirector()->getWinSize();
        CCRect rect=CCRectMake(0,0,size.width,size.height); //创建一个逻辑矩形，范围是屏幕的大小，用于判断边界
        
        if(rect.containsPoint(position))
        {
            jl->setPosition(position);
        }
    }  
}

