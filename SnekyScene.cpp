//
//  SnekyScene.m
//  xiyouji
//
//  Created by weng xiangxun on 13-4-7.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//
 
#include "SnekyScene.h"

using namespace cocos2d;


CCScene* SnekyScene::scene()
{
    CCScene *scene = CCScene::create();
    SnekyScene *layer = SnekyScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化
bool SnekyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    // Sneaky Input
    float buttonRadius=50;
    
    buttonA=new SneakyButton();
    buttonA->autorelease();
    buttonA->initWithRect(CCRectZero);
    buttonA->setIsToggleable(false);
    buttonA->setIsHoldable(true);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    SneakyButtonSkinnedBase *buttonASkin=new SneakyButtonSkinnedBase();
    buttonASkin->autorelease();
    buttonASkin->init();
    buttonASkin->setPosition(ccp(size.width-buttonRadius,buttonRadius));
    buttonASkin->setDefaultSprite(CCSprite::create("button-default.png"));
    // buttonASkin->setDisabledSprite(CCSprite::spriteWithFile("button-disabled.png"));
    buttonASkin->setPressSprite(CCSprite::create("button-pressed.png"));
    buttonASkin->setActivatedSprite(CCSprite::create("button-activated.png"));
    buttonASkin->setButton(buttonA);
    
    this->addChild(buttonASkin);
    
    float joystickRadius=50;
    
    joystick=new SneakyJoystick();
    joystick->autorelease();
    joystick->initWithRect(CCRectZero);
    joystick->setAutoCenter(true);
    joystick->setHasDeadzone(true);
    joystick->setDeadRadius(10);
    
    SneakyJoystickSkinnedBase *joystickSkin=new SneakyJoystickSkinnedBase();
    joystickSkin->autorelease();
    joystickSkin->init();
//    spriteWithFile("button-disabled.png")
    joystickSkin->setBackgroundSprite(CCSprite::create("button-disabled.png"));
    joystickSkin->setThumbSprite(CCSprite::create("button-disabled.png"));
    joystickSkin->getThumbSprite()->setScale(0.5f);
    joystickSkin->setPosition(ccp(joystickRadius,joystickRadius));
    joystickSkin->setJoystick(joystick);
    
    this->addChild(joystickSkin);
    
    this->scheduleUpdate();
    return true;
}
#define FIRE_INTERVAL 0.3f
float SnekyScene::fireTime=0;
void SnekyScene::update(float dt)
{
	CCPoint velocity=joystick->getVelocity();
	if(velocity.x!=0||velocity.y!=0)
	{
		CCLOG("joystick:[%f,%f]",velocity.x,velocity.y);
	}
    
	fireTime+=dt;
	
	if(buttonA->getIsActive()&&fireTime>=FIRE_INTERVAL)
	{
		CCLOG("buttonA pressed.");
		fireTime=0;
	}
}


