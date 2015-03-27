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
    //设置随机算子
    //time(0)返回当前系统时间（秒数）。
    srand(time(0));
    
    //加载资源
    this->loadResource();

    
    
//    m_level=level;
    
    
    
//    //向当前场景中添加地图层
    MapLayer *maplayer= MapLayer::createMapLayer(level);
    this->addChild(maplayer);
   
    m_level=level; 
     
    GameLayer *gameLayer =GameLayer::createGameLayer(level);
    this->addChild(gameLayer);
    
    
    
    
    
    return true;
    
}
void GameScene:: onEnterTransitionDidFinish()
{
    

    
    const char*musicName =CCString::createWithFormat("bg%d.mp3",m_level)->getCString();
    CCScene::onEnterTransitionDidFinish();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musicName);
   
    
}
void GameScene::loadResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Game/sp_all.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Game/bullet_lv.plist");

}

