//
//  SnekyScene.h
//  xiyouji
//
//  Created by weng xiangxun on 13-4-7.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//
#ifndef __SnekyScene_H__
#define __SnekyScene_H__

#include "cocos2d.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
class SnekyScene : public cocos2d::CCLayer
{
    
protected:
    //类成员
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SnekyScene);
    
private:
    SneakyButton *buttonA;
	SneakyJoystick *joystick;
	static float fireTime;
	void update(float dt);
};


#endif // __SnekyScene.h_H__