//
//  Enemy.cpp
//  PlaneGame
//
//  Created by metc on 15/3/25.
//
//

#include "Enemy.h"
Enemy* Enemy::createEnemy(EnemyType type) {
    Enemy *enemy = new Enemy;
    if (enemy && enemy->initEnemy(type)) {
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool Enemy::initEnemy(EnemyType type){
    const char* imageName = CCString::createWithFormat("e%d.png", type + 1)->getCString();
    if (!CCSprite::initWithFile(imageName)) {
        return false;
    }
    switch ((int)type) {
        case ENEMY1:
            m_hp = 1;
            break;
        case ENEMY2:
            m_hp = 2;
            break;
        case ENEMY3:
            m_hp = 3;
            break;
        case ENEMY4:
            m_hp = 4;
            break;
    }
    //速度随机 3 - 7
    m_speed = rand() % 5 + 3;
    
    this->schedule(schedule_selector(Enemy::move));
    
    return true;
}
//伤害
void Enemy::hurt(int hurtNum){
    m_hp -= hurtNum;
    if (m_hp <= 0) {
        this->die();
    }
}
void Enemy::move(float dt){
    this->setPositionY(this->getPositionY() - m_speed);
    if (this->getPositionY() <= -this->getContentSize().height * 0.5) {
        this->die();
    }
}
void Enemy::remove(){
    this->removeFromParent();
}
//敌人死亡
void Enemy::die(){
    //爆炸例子效果
    //移除敌人
    this->remove();
}



