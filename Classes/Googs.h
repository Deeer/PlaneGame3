//
//  Googs.h
//  PlaneGame
//
//  Created by METC on 15/3/26.
//
//

#ifndef __PlaneGame__Googs__
#define __PlaneGame__Googs__

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;
class Goods: public CCSprite
{
    
public:
    CREATE_FUNC(Goods);
    bool init();
    CC_SYNTHESIZE_READONLY(int, m_addAtk, AddAtk);
    CC_SYNTHESIZE_READONLY(bool, m_isDie, Die);
    CC_SYNTHESIZE_READONLY(bool, m_isColliossin, ISCollision);
    void willDie();
//    void willDie();
private:
    float m_speed;
    void move();
    void Die();
};

#endif /* defined(__PlaneGame__Googs__) */
