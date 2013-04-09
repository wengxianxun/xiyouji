//
//  ShunSprite.h
//  xiyouji
//
//  Created by weng xiangxun on 13-4-7.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//
#ifndef __ShunSprite.h_H__
#define __ShunSprite.h_H__

#include "cocos2d.h"

class ShunSprite : public cocos2d::CCSprite
{
    
protected:
    //类成员
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
        
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShunSprite);
    
    void createAnimation();
};


#endif // __ShunSprite.h_H__