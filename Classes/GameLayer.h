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
#include "Plane.h"
USING_NS_CC;

class GameLayer:public CCLayer
{
    
    
public:
//    static GameLayer*createGameLayer(int level);
//    bool initGameLayer(int  level);
    CREATE_FUNC(GameLayer);
    bool init();
      void onEnterTransitionDidFinish();
private:
    Plane* m_plane;
    CCPoint m_beginPoint;
    void addPlane();
    
    void openTouch();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    // optional
    
   void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    
};

#endif /* defined(__PlaneGame__GameLayer__) */
