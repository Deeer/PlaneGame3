//
//  MapLayer.h
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#ifndef __PlaneGame__MapLayer__
#define __PlaneGame__MapLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MapLayer :public CCLayer
{
    
public:
 
    //当前节点被加到父节点中会调用这个方法
    void onEnter();
    //当前节点从父节点中移除时会调用该方法
    void onExit();
    //将要做场景的动画
    virtual void onEnterTransitionDidFinish();
    //跳转场景动画完成
    virtual void onExitTransitionDidStart();
    
    static MapLayer*createMapLayer(int level);
    bool initMapLayer(int level);
    
private:
    void update(float dt);
    CCSprite *m_map1;
    CCSprite *m_map2;
};


#endif /* defined(__PlaneGame__MapLayer__) */
