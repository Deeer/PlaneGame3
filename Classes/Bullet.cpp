//
//  Bullet.cpp
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#include "Bullet.h"
#include "define.h"

Bullet* Bullet::createBullet(int bulletLevel)
{
    Bullet *bullet =new Bullet;
    if (bullet&&bullet->initBullet(bulletLevel)) {
        bullet->autorelease();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}


bool Bullet::initBullet(int bulletLevel){
    
    const char*frameName = CCString::createWithFormat("1_%d.png",bulletLevel)->getCString();
    
    if (!CCSprite::initWithSpriteFrameName(frameName)) return false;
    
    m_attack =bulletLevel;
    m_speed =20+0.3*bulletLevel;
    
    this->schedule(schedule_selector(Bullet::move));
    
    return  true;
    
}


float m_speed;
//子弹移动
void Bullet::move(float dt)
{
    this ->setPositionY(this->getPositionY()+m_speed);
    if (this->getPositionY()>= SCREEN.height+this->getContentSize().height*0.5 ) {
        
        this->removeBullet();
    }
}
//移除子弹
void Bullet::removeBullet()
{
    this->removeFromParent();
}
