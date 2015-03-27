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
            m_score =100;
            break;
        case ENEMY2:
            m_hp = 2;
           m_score =200;
            break;
        case ENEMY3:
            m_hp = 3;
            m_score =300;
            break;
        case ENEMY4:
            m_hp = 4;
            m_score =400;
        case ENEMY5:
            m_hp = 5;
            m_score =500;
            break;
    }
    m_maxHp=m_hp;
    //速度随机 3 - 7
    m_speed = rand() % 5 + 3;
    
    CCSprite *sprite= CCSprite::create("sp_all.png");
    this->addChild(sprite);
    sprite->setPosition(ccp(this->getContentSize().width * 0.5, this->getContentSize().height));
    CCSprite *sprite2= CCSprite::create("sp_all2.png");
//    this->addChild(sprite2);
     progerss=CCProgressTimer::create(sprite2);
    
    progerss->setType(kCCProgressTimerTypeBar);
    progerss->setMidpoint(ccp(0, 0));
    progerss->setBarChangeRate(ccp(1, 0));
    progerss->setPercentage(100);
    this->addChild(progerss);

    
    
     progerss->setPosition(ccp(this->getContentSize().width * 0.5, this->getContentSize().height));
    
    this->schedule(schedule_selector(Enemy::move));
    m_isDie=false;
//    m_isOut=false;
    std::cout<<m_isDie<<"----"<<std::endl;
    return true;
}
//伤害
void Enemy::hurt(int hurtNum){
    this->stopAllActions();
    CCBlink *blink =CCBlink::create(0.2, 2);
    this->runAction(blink);
    m_hp -= hurtNum;
    progerss ->setPercentage((float)(m_hp*1.0/m_maxHp*100));
    
    
    
    if (m_hp <= 0) {
        this->die();
    }
}

#warning BUG...
void Enemy::move(float dt){
    this->setPositionY(this->getPositionY() - m_speed);
    if (this->getPositionY() <= -this->getContentSize().height * 0.5) {
        this->outer();
    }
}
//void Enemy::remove(){
//    this->removeFromParent();
//}
//敌人死亡
void Enemy::die(){
//爆炸例子效果
//移除敌人
    m_isDie=true;
    
    
    CCParticleSystemQuad *system= CCParticleSystemQuad::create("particle_boom.plist");
    this->getParent()->addChild(system);
    
    system->setPosition(this->getPosition());
    
    system->setAutoRemoveOnFinish(true);
    
    
}
void Enemy::outer()
{
    m_isOut=true;
}



