//
//  ShunSprite.m
//  xiyouji
//
//  Created by weng xiangxun on 13-4-7.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "ShunSprite.h"

using namespace cocos2d;

// 初始化
bool ShunSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    //动画
    this->createAnimation();
    return true;
}

void ShunSprite::createAnimation()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("shunwukong.png");
    
    // manually add frames to the frame cache
    int xx = 70;
    int yy = 65;
    CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*0, yy*0, xx, yy));
    CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*1, yy*0, xx, yy));
    CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*2, yy*0, xx, yy));
    CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*3, yy*0, xx, yy));
    CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*0, yy*1, xx, yy));
    CCSpriteFrame *frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*1, yy*1, xx, yy));
    CCSpriteFrame *frame6 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*2, yy*1, xx, yy));
    CCSpriteFrame *frame7 = CCSpriteFrame::createWithTexture(texture, CCRectMake(xx*3, yy*1, xx, yy));
    
    //
    // Animation using Sprite BatchNode
    //
    CCSprite* sprite = CCSprite::createWithSpriteFrame(frame0);
    sprite->setPosition( ccp( s.width/2-80, s.height/2) );
    addChild(sprite);
    
    CCArray* animFrames = CCArray::createWithCapacity(6);
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    animFrames->addObject(frame3);
    animFrames->addObject(frame4);
    animFrames->addObject(frame5);
    animFrames->addObject(frame6);
    animFrames->addObject(frame7);
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCActionInterval* seq = (CCActionInterval*)(CCSequence::create( animate,
                                                                   CCFlipX::create(true),
                                                                   animate->copy()->autorelease(),
                                                                   CCFlipX::create(false),
                                                                   NULL) );
    
    sprite->runAction(CCRepeatForever::create( animate ) );
}

