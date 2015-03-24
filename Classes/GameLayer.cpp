//
//  GameLayer.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "GameLayer.h"
#include "define.h"
bool GameLayer::init()
{
    if (!CCLayer::init()) return false;
    

    
    return true;
    
    
}
void GameLayer::onEnterTransitionDidFinish()
{
    
    
    CCLayer::onEnterTransitionDidFinish();
    this->addPlane();
   
}
 void  GameLayer::addPlane()
{
    //创建飞机
    m_plane=Plane::create();
    this->addChild(m_plane);
    //
    m_plane->setPosition(ccp(SCREEN.width*0.5, -m_plane->getContentSize().height*0.5));
    CCMoveTo *moveTo =CCMoveTo::create(1, SCREEN_POSITION(0.5, 0.2));
    CCCallFunc *callBack=CCCallFunc::create(this, callfunc_selector(GameLayer::openTouch));
    CCSequence *seq =CCSequence::create(moveTo,callBack);
    m_plane->runAction(seq);
    
    
}

void GameLayer::openTouch()
{
    //开启触摸
    this->setTouchEnabled(true);
    //设置触摸模式为单点模式
    this->setTouchMode(kCCTouchesOneByOne);
}

bool  GameLayer:: ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

    m_beginPoint=pTouch->getLocation();
    
    return true;

    
};
 void GameLayer:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
     CCPoint moveDis =pTouch->getLocation()-m_beginPoint;
     
     
     m_plane->setPosition(m_plane->getPosition()+moveDis);
     if (m_plane->getPosition().x>(SCREEN.width-m_plane->getContentSize().width*0.5)) {
         m_plane->setPositionX(SCREEN.width-m_plane->getContentSize().width*0.5);
     }
     if (m_plane->getPosition().x<(m_plane->getContentSize().width*0.5)) {
         m_plane->setPositionX(m_plane->getContentSize().width*0.5);
     }
     if (m_plane->getPosition().y>(SCREEN.height-m_plane->getContentSize().height*0.5)) {
         m_plane->setPositionY(SCREEN.height-m_plane->getContentSize().height*0.5);
     }
     if (m_plane->getPosition().y<(m_plane->getContentSize().height*0.5)) {
         m_plane->setPositionY(m_plane->getContentSize().height*0.5);
     }
     

     m_beginPoint=pTouch->getLocation();
 };
