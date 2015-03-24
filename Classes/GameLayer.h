//
//  GameLayer.h
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#ifndef __PlaneGame__GameLayer__
#define __PlaneGame__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GameLayer:public CCLayer
{
public:
    static GameLayer*createGameLayer(int level);
    bool initGameLayer(int  level);
    
};

#endif /* defined(__PlaneGame__GameLayer__) */
