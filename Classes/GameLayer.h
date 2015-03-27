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
#include "Bullet.h"
#include "Enemy.h"
#include "Googs.h"
USING_NS_CC;

class GameLayer:public CCLayer
{
    
    
public:
//    static GameLayer*createGameLayer(int level);
//    bool initGameLayer(int  level);
//    CREATE_FUNC(GameLayer);
//    bool init();
    static GameLayer *createGameLayer(int level);
    bool initGameLayer(int level);
      void onEnterTransitionDidFinish();
    void shootBullet();
     ~GameLayer();
   
private:
    Plane* m_plane;
    CCPoint m_beginPoint;
    //子弹数组
    CCArray *m_bullets;
    //敌人数组
    CCArray *m_enemys;
    //货物数组
    CCArray *m_goods;
  
    
    void addPlane();
    void addScore(int addNum);
    
    
    void addBullet();
    void addEnemy(float dt);
    void addCloud(float dt);
    void addGood(float dt);
    void openTouch();
    void bulletAndEnemyCollision();
    void goodReceived();
    void removeBullet();
  
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void gameWin();
    void pause(CCNode *node);
   void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void goNewGameSence();
    //分数
    int  m_score;
    int m_level;
    CCLabelBMFont *m_scoreFont;
    void removeEnemy();
    void removeGoods();
    
    void addWinLayer();
    
};

#endif /* defined(__PlaneGame__GameLayer__) */
