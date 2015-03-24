//
//  MapLayer.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "MapLayer.h"
MapLayer* MapLayer:: createMapLayer(int level)
{
    MapLayer *layer =new MapLayer;
    if (layer&&layer->initMapLayer(level)) {
        
        layer->autorelease();
        return layer;
    
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}
bool  MapLayer:: initMapLayer(int level){
    if (!CCLayer::init()) {
        return false;
        
    }
    
    const char*  mapImageName =CCString::createWithFormat("BG/img_bg_level_%d.jpg",level)->getCString();
    m_map1 =CCSprite::create(mapImageName);
    m_map2 =CCSprite::create(mapImageName);
    m_map1 ->setAnchorPoint(CCPointZero);
    m_map2 ->setAnchorPoint(CCPointZero);
    m_map2 ->setPosition(ccp(0, m_map1->getContentSize().height));
    this->addChild(m_map1);
    this->addChild(m_map2);
    
    this->scheduleUpdate();
//    this->schedule(schedule_selector(MapLayer::update), 1);
    
    return true;
    
}
void MapLayer::update(float dt)
{
    
    m_map1->setPositionY(m_map1->getPositionY()-2);
    m_map2->setPositionY(m_map2->getPositionY()-2);
    if (m_map1->getPositionY()<=-m_map1->getContentSize().height) {
    
        m_map1->setPositionY(m_map2->getContentSize().height+m_map2->getPositionY());
//        CCLog("-1--%f",m_map1->getPositionY());
    }
    if (m_map2->getPositionY()<=-m_map2->getContentSize().height) {
        m_map2->setPositionY(m_map1->getContentSize().height+m_map1->getPositionY());
//         CCLog("-2--%f",m_map2->getPositionY());
    }
}
void MapLayer::onEnter()
{
    CCLayer::onEnter();
};
void MapLayer::onExit()
{
    CCLayer::onExit();
    
};
//将要做场景的动画
 void MapLayer:: onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}
//跳转场景动画完成
void MapLayer:: onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}




