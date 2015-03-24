//
//  GameScene.h
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#ifndef __PlaneGame__GameScene__
#define __PlaneGame__GameScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GameScene :public CCScene{
    
public:
//    CREATE_FUNC(GameScene);
    static GameScene*createGameSence(int level);
    bool initGameSence(int level);
    void onEnterTransitionDidFinish();
private:
    int m_level;
    //加载资源
    void loadResource();
};


#endif /* defined(__PlaneGame__GameScene__) */
