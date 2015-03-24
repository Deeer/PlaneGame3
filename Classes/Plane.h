//
//  Plane.h
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#ifndef __PlaneGame__Plane__
#define __PlaneGame__Plane__

#include <stdio.h>
#include  "cocos2d.h"
USING_NS_CC;
class Plane :public CCSprite{
    
public:
    CREATE_FUNC(Plane);
    bool init();
    
    
    //声明了一个保护变量 ，声明并实现了一个get方法
    CC_SYNTHESIZE_READONLY(int, m_PlaneLevel, PlaneLevel);
    
    //升级方法
    void upLevel(int upNum);
    
    //发射子弹
    void shootBullet();
    
    
};

#endif /* defined(__PlaneGame__Plane__) */
