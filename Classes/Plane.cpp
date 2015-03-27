//
//  Plane.cpp
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#include "Plane.h"
#include "GameLayer.h"
bool Plane::init()
{//精灵中的纹理对象负责显示
//    setTexture(NULL);
    

    
    if (!CCSprite::initWithSpriteFrameName("role0.png")) {
        return false;
    }

    m_PlaneLevel=1;
   
    
    
    CCSprite *fire =CCSprite::create();
    CCAnimation *animation =CCAnimation::create();
    for (int i=0 ; i<4; i++) {
        const char *frameName =CCString::createWithFormat("role_fire%d.png",i)->getCString();
        CCSpriteFrame *spriteFrame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
        
        animation->addSpriteFrame(spriteFrame);
         }
        animation->setDelayPerUnit(0.05);
        animation->setLoops(-1);
        CCAnimate *animate =CCAnimate::create(animation);
        fire->runAction(animate);
        fire->setPosition(ccp(32, -30));
        this->addChild(fire);
       this->schedule(schedule_selector(Plane::shootBullet), 0.5);

    
    return true;
}



void Plane::upLevel(int upNum)
{
    
    m_PlaneLevel+=upNum;
    if (m_PlaneLevel>35) {
        m_PlaneLevel=35;
    }
}
void Plane::shootBullet(float dt)
{
    GameLayer *gameLayer= (GameLayer*)this->getParent();
    gameLayer->shootBullet();
}
