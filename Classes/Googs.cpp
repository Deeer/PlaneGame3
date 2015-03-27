//
//  Googs.cpp
//  PlaneGame
//
//  Created by METC on 15/3/26.
//
//

#include "Googs.h"
bool Goods::init(){
    
    
    if (!CCSprite::initWithFile("goods.png")) {
        return false;
    }
    m_isDie=false;
    int index =rand()%3;
    m_speed =rand()%4+2;
    
    switch ( index) {
        case 0:
            this->setColor(ccc3(255, 0, 0));
            m_addAtk=1;
            break;
            
        case 1:
            this->setColor(ccc3(0, 255, 0));
            m_addAtk=2;
            break;
        case 2:
            this->setColor(ccc3(0, 0, 255));
            m_addAtk=3;
            break;
      
    }
    
    CCRotateBy *roteta=CCRotateBy::create(0.5, 360);
    this->runAction(CCRepeatForever::create(roteta));
    
    this->schedule(schedule_selector(Goods::move));
    return true;
}
void Goods::move()
{
    this->setPositionY(this->getPositionY()-m_speed);
    if (this->getPositionY()<=-this->getContentSize().height*.5) {
        this->Die();
    }
}
void Goods::Die()
{
    m_isDie=true;
}
void Goods::willDie()
{
    this->unscheduleAllSelectors();
    this->Die();
    m_isColliossin=true;
    CCScaleTo *scaleTo= CCScaleTo::create(1, 1.5);
    CCFadeIn *fadeIn =CCFadeIn::create(1);
    CCSpawn*spwan=CCSpawn::create(scaleTo,fadeIn,NULL);
    CCCallFunc *func= CCCallFunc::create(this, callfunc_selector(Goods::Die));
    CCSequence *sqe =CCSequence::create(spwan,func,NULL);
    this->runAction(sqe);
}