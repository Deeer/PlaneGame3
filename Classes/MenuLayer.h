//
//  MenuLayer.h
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#ifndef __PlaneGame__MenuLayer__
#define __PlaneGame__MenuLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MenuLayer :public CCLayerColor{
    
    
public:
    static CCScene *scene();
    CREATE_FUNC(MenuLayer);
    bool init();
    void addLogo();
    void addBackGround();
    void addTitle();
    void addMenu();
    void goGameSence();
};

#endif /* defined(__PlaneGame__MenuLayer__) */
