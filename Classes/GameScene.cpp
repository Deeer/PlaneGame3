//
//  GameScene.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "GameScene.h"
#include "MapLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
GameScene* GameScene::createGameSence(int level)
{
    GameScene *secne =new GameScene;
    if (secne &&secne->initGameSence(level)) {

        secne->autorelease();//内存管理
        return secne;
    }
    CC_SAFE_DELETE(secne);
    return NULL;
}
bool GameScene::initGameSence(int level)
{
    if (!CCScene::init()) return false;
    
    
    
//    m_level=level;
    
    
    
    //向当前场景中添加地图层
    MapLayer *maplayer= MapLayer::createMapLayer(level);
    this->addChild(maplayer);
   
    
    
//    GameLayer *GameLayer =GameLayer::createGameLayer(level);
//    this->addChild(GameLayer);
    
    
    
    
    return true;
    
}
void GameScene:: onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TheDawn.mp3");
    
}