//
//  Cloud.cpp
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#include "Cloud.h"
bool Cloud::init()
{
    if(!CCSprite::initWithFile("BG/img_cloud_1.png")) return false;
    
    
    int num =rand()%2;
    switch (num) {
        case 0:
        {this->setScale(0.7);
            m_speed=3;
            this->setZOrder(-10);
        }
            break;
         case 1:
        {this->setScale(1.2);
            this->setZOrder(10);
            m_speed=6;}
            break;
    }
    
    this->schedule(schedule_selector(Cloud::move));
    
    return true;

}
void Cloud::move(float dt)
{
    this->setPositionY(this->getPositionY()-m_speed);
    if (this->getPositionY()<=-this->getContentSize().height*.5) {
        this->removeCloud();
    }
    
    
}
void Cloud:: removeCloud()
{
    this->removeFromParent();
}