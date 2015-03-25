//
//  Bullet.h
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#ifndef __PlaneGame__Bullet__
#define __PlaneGame__Bullet__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Bullet :public CCSprite{
    
    public :
    static Bullet* createBullet(int bulletLevel);
    bool initBullet(int bulletLevel);
    CC_SYNTHESIZE_READONLY(int, m_attack, Attack);
    CC_SYNTHESIZE_READONLY(bool, m_isDie, Die);
    void die();
private:
    float m_speed;
    //子弹移动
    void move(float dt);
    //移除子弹
//    void removeBullet();
    //子弹死亡
    
    
    
};


#endif /* defined(__PlaneGame__Bullet__) */
