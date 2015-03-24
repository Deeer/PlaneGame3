//
//  GameLayer.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "GameLayer.h"
GameLayer*GameLayer::createGameLayer(int level)
{
    GameLayer *gameLayer =new GameLayer;
    if (gameLayer && gameLayer->initGameLayer(level)) {
        gameLayer->autorelease();
        return gameLayer;
    }
    CC_SAFE_DELETE(gameLayer);
    return NULL;
    
}
bool GameLayer::initGameLayer(int  level)
{
    if (!GameLayer::init()) {
        return false;
    }
    return true;
    
    
}