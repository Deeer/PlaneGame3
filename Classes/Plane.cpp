//
//  Plane.cpp
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#include "Plane.h"
bool Plane::init()
{//精灵中的纹理对象负责显示
//    setTexture(NULL);
    

    
    if (!CCSprite::initWithSpriteFrameName("role0.png")) {
        return false;
    }
    m_PlaneLevel=1;
    return true;
}

void Plane::upLevel(int upNum)
{
    m_PlaneLevel+=upNum;
}
void Plane::shootBullet()
{
    
}
