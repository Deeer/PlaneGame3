//
//  Enemy.h
//  PlaneGame
//
//  Created by metc on 15/3/25.
//
//

#ifndef __PlaneGame__Enemy__
#define __PlaneGame__Enemy__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

typedef enum {
    ENEMY1,
    ENEMY2,
    ENEMY3,
    ENEMY4,
    ENEMY5,
    ENEMY_COUNT
} EnemyType;

class Enemy : public CCSprite {
public:
    static Enemy* createEnemy(EnemyType type);
    bool initEnemy(EnemyType type);
    //伤害
    void hurt(int hurtNum);
    CC_SYNTHESIZE_READONLY(bool, m_isDie, Die);
    CC_SYNTHESIZE_READONLY(bool, m_isOut, Outer);
    CC_SYNTHESIZE_READONLY(int, m_score, Score);
private:
    CCProgressTimer *progerss;
    int m_maxHp;
    int m_hp;
    float m_speed;
    void move(float dt);
    //敌人死亡
    void die();
    void outer();
};
#endif /* defined(__PlaneGame__Enemy__) */










