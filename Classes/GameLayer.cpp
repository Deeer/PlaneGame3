//
//  GameLayer.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "GameLayer.h"
#include "define.h"
#include "SimpleAudioEngine.h"
#include "Cloud.h"
#include "GameScene.h"
using namespace CocosDenshion;
GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(m_bullets);
    CC_SAFE_RELEASE(m_enemys);
    CC_SAFE_RELEASE(m_goods);
    
}

GameLayer * GameLayer::createGameLayer(int level)
{
    GameLayer *layer= new GameLayer;
    if (layer &&layer->initGameLayer(level)) {
        
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return false;
}

bool GameLayer::initGameLayer(int  level)
{
    if (!CCLayer::init()) return false;
    m_level=level;
    m_score =0;
    m_scoreFont=CCLabelBMFont::create("0", "MyFont.fnt");
     this->addChild(m_scoreFont);
    m_scoreFont->setAnchorPoint(ccp(0, 1));
    m_scoreFont->setPosition(SCREEN_POSITION(0, 1));
    
    
    
    
    
    m_bullets = CCArray::create();
    m_bullets->retain(); //+1
    //敌人数组
    m_enemys = CCArray::create();
    CC_SAFE_RETAIN(m_enemys); //+1
    
    m_goods =CCArray::create();
    m_goods->retain();
    
    return true;
    
    
}
void GameLayer::addScore(int addNum)
{
    m_score+=addNum;
    m_scoreFont->setString(CCString::createWithFormat("%d",m_score)->getCString());
    if (m_score>=5000) {
        this->gameWin();
    }
    
}
void GameLayer::onEnterTransitionDidFinish()
{
    
    
    CCLayer::onEnterTransitionDidFinish();
    
    this->schedule(schedule_selector(GameLayer::addCloud), 2);
    
    this->addPlane();
    //添加敌人
    this->schedule(schedule_selector(GameLayer::addEnemy), 1);
    //检测碰撞
    this->schedule(schedule_selector(GameLayer::bulletAndEnemyCollision));
    //释放要移除的子弹对象
    this->schedule(schedule_selector(GameLayer::removeBullet));
    //释放要移除的敌人对象
    this->schedule(schedule_selector(GameLayer::removeEnemy));
    //添加道具
   this->schedule(schedule_selector(GameLayer::addGood), 1);
    //工具获取
    this->schedule(schedule_selector(GameLayer::goodReceived),1);
    
    this->schedule(schedule_selector(GameLayer::removeGoods), 1);
}
void GameLayer::addCloud(float dt)
{
    Cloud *cloud =Cloud::create();
    this->addChild(cloud);
    //CCRANDOM_0_1()去的0-1之间的随机数
    float X =CCRANDOM_0_1()*SCREEN.width;
    float Y =SCREEN.height+cloud->getContentSize().height*.5;
    cloud->setPosition(ccp(X, Y));
    
    
}
 void  GameLayer::addPlane()
{
    //创建飞机
    m_plane=Plane::create();
    this->addChild(m_plane);
    m_plane->setAnchorPoint(ccp(0.5, 1));
    //
    m_plane->setPosition(ccp(SCREEN.width*0.5, -m_plane->getContentSize().height*0.5));
    CCMoveTo *moveTo =CCMoveTo::create(1, SCREEN_POSITION(0.5, 0.2));
    CCCallFunc *callBack=CCCallFunc::create(this, callfunc_selector(GameLayer::openTouch));
 
    CCEaseBackInOut *backInOut =CCEaseBackInOut::create(moveTo);
       CCSequence *seq =CCSequence::create(backInOut,callBack);

    m_plane->runAction(seq);
    
    
}
void GameLayer::addGood(float dt)
{
    Goods *good =Goods::create();
    this->addChild(good);
    good->setPosition(ccp(CCRANDOM_0_1()*SCREEN.width, SCREEN.height+good->getContentSize().height*.5));
    m_goods->addObject(good);
    
}
void GameLayer::addEnemy(float dt) {
    int type = rand() % ENEMY_COUNT;
    Enemy *enemy = Enemy::createEnemy((EnemyType)type);
    float x = CCRANDOM_0_1() * SCREEN.width;
    float y = SCREEN.height + enemy->getContentSize().height * 0.5;
    enemy->setPosition(ccp(x,y));
    this->addChild(enemy);
    //把敌人加到数组中
    m_enemys->addObject(enemy);
}

void GameLayer::addBullet()
{
    
    Bullet *bullet= Bullet::createBullet(m_plane->getPlaneLevel());
    bullet->setPosition(m_plane->getPosition());
    this->addChild(bullet);
}

void GameLayer::openTouch()
{
    //开启触摸
    this->setTouchEnabled(true);
    //设置触摸模式为单点模式
    this->setTouchMode(kCCTouchesOneByOne);
}

bool  GameLayer:: ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

    m_beginPoint=pTouch->getLocation();
    
    return true;

    
};
 void GameLayer:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
     CCPoint moveDis =pTouch->getLocation()-m_beginPoint;
     
     
     m_plane->setPosition(m_plane->getPosition()+moveDis);
     if (m_plane->getPosition().x>(SCREEN.width-m_plane->getContentSize().width*0.5)) {
         m_plane->setPositionX(SCREEN.width-m_plane->getContentSize().width*0.5);
     }
     if (m_plane->getPosition().x<(m_plane->getContentSize().width*0.5)) {
         m_plane->setPositionX(m_plane->getContentSize().width*0.5);
     }
     if (m_plane->getPosition().y>(SCREEN.height-m_plane->getContentSize().height*0.5)) {
         m_plane->setPositionY(SCREEN.height-m_plane->getContentSize().height*0.5);
     }
     if (m_plane->getPosition().y<(m_plane->getContentSize().height*0.5)) {
         m_plane->setPositionY(m_plane->getContentSize().height*0.5);
     }
     

     m_beginPoint=pTouch->getLocation();
 };
void GameLayer::shootBullet()
{
    Bullet *bullet=Bullet::createBullet(m_plane->getPlaneLevel());
    bullet->setZOrder(-1);
    bullet->setPosition(m_plane->getPosition());
    this->addChild(bullet); //+1  bullet->retain();
    //把子弹加到数组中
    m_bullets->addObject(bullet);//+1
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");
}
//检测子弹是否打中敌人
void GameLayer::bulletAndEnemyCollision() {
    for (int i = 0; i < m_bullets->count(); i++) {
        Bullet *bullet = (Bullet*)m_bullets->objectAtIndex(i);
        
        for (int j = 0; j < m_enemys->count(); j++) {
            if (!bullet->getDie()  ) { //不是死的子弹 才可以打不是死的敌人
                Enemy *enemy = (Enemy*)m_enemys->objectAtIndex(j);
                
              if (!enemy->getDie()) { //如果敌人是活的 做碰撞检测
                
                if (bullet->boundingBox().intersectsRect(enemy->boundingBox())) {
                    //                子弹打中敌人
                    SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
                    enemy->hurt(bullet->getAttack());
                    
                    CCLog("子弹打中敌人");
                    //子弹死亡
                    bullet->die();
                    }
                }
            }
        }
    }
}


void GameLayer::goodReceived()
{
    
        for (int  i=0; i<m_goods->count(); i++) {
            Goods *good =(Goods*)m_goods->objectAtIndex(i);
            if (m_plane->boundingBox().intersectsRect(good->boundingBox()) ) {
//                CCScaleTo *scale =CCScaleTo::create(0.01, 1.5);
//                CCFadeOut *fateOu=CCFadeOut::create(0.01);
//                CCSpawn *spw =CCSpawn::create(scale,fateOu,NULL);
//                good->runAction(spw);
//                good->getAddAtk();
                m_plane->upLevel( good->getAddAtk());
                
                good->willDie();
                
                
            }
       
        
    }
}




void GameLayer::removeBullet() {
    CCArray *removeArray = CCArray::create();
    for (int i = 0; i < m_bullets->count(); i++) {
        Bullet *bullet = (Bullet*)m_bullets->objectAtIndex(i);
        if (bullet->getDie()) {
            //把死亡的子弹加到 移除数组中
            removeArray->addObject(bullet);
        }
       
    }
    
    for (int i = 0; i < removeArray->count(); i++) {
        Bullet *removeBullet = (Bullet*)removeArray->objectAtIndex(i);
        this->removeChild(removeBullet); // -1
        m_bullets->removeObject(removeBullet); //-1
    }
    removeArray->removeAllObjects();//-1
}
void GameLayer::removeGoods()
{
    CCArray *removeArray =CCArray::create();
    for (int i=0; i<m_goods->count(); i++) {
        Goods *good=(Goods*)m_goods->objectAtIndex(i);
        if (good->getDie()) {
            removeArray ->addObject(good);
            
        }
        
    }
    
    for (int i =0;i<removeArray->count() ; i++) {
        Goods *removeGood= (Goods*)removeArray->objectAtIndex(i);
        this->removeChild(removeGood); // -1
        m_enemys->removeObject(removeGood); //-1
        
    }
    
    removeArray->removeAllObjects();//-1

    
}
void GameLayer::removeEnemy()
{
    
    CCArray *removeArray=CCArray::create();
    for (int i=0; i<m_enemys->count();i++) {
        Enemy *enemy =(Enemy *)m_enemys->objectAtIndex(i);
        if (enemy->getDie()||enemy->getOuter()) {
            removeArray ->addObject(enemy);    
        }
 
    }
    
        for (int i =0;i<removeArray->count() ; i++) {
            Enemy *removeEnemy= (Enemy*)removeArray->objectAtIndex(i);
            this->removeChild(removeEnemy); // -1
            m_enemys->removeObject(removeEnemy); //-1
            if (removeEnemy->getDie()) {
             this->addScore(removeEnemy->getScore());
            }
           
        }
    
     removeArray->removeAllObjects();//-1
    
}

void GameLayer::gameWin()
{
//    this->pause(this->getParent());
//    this->pause(CCDirector::sharedDirector()->getRunningScene());
    //获取当期正在允许的对象
//    this->unscheduleAllSelectors();
//    this->GameLayer::addWinLayer();
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    GameScene *scene = (GameScene*)this->getParent();
    this->pause(scene);
    
    
    
    for (int  i= 0; i<m_bullets->count(); i++) {
        Bullet *enemy =(Bullet *)m_bullets->objectAtIndex(i);
        enemy->setVisible(false);
        
    }
    
    
    //把敌人隐藏
    for (int  i= 0; i<m_enemys->count(); i++) {
        Enemy *enemy =(Enemy *)m_enemys->objectAtIndex(i);
        enemy->setVisible(false);
        
    }
    
    
    
    CCMoveTo *moveTo = CCMoveTo::create(1,ccp(m_plane->getPositionX(),  SCREEN.height + 100));
    m_plane->runAction(moveTo);
    CCCallFunc *func =CCCallFunc::create(this, callfunc_selector(GameLayer::addWinLayer));
    CCSequence *sqe =CCSequence::create(moveTo,func,NULL);
    m_plane->runAction(sqe);
    
//    this->unscheduleUpdate();
    
}
void GameLayer::pause(CCNode *node)
{
    
    int count =node->getChildrenCount();
    for (int i =0; i<count; i++) {
        CCNode *ChildNode=(CCNode*)node->getChildren()->objectAtIndex(i);
        this->pause(ChildNode);
    }
    node->unscheduleAllSelectors();
}
 void GameLayer::addWinLayer()
{
//    CCLayerColor *colorLayer =CCLayerColor::create(ccc4(0, 0, 0, 125));
    
    CCLayerGradient  *layer= CCLayerGradient::create(ccc4(255, 0, 0, 255), ccc4(0, 255, 0, 0));
    layer->setOpacity(0);
    layer->runAction(CCFadeIn::create(1));
    
    CCScene *sec=  CCDirector::sharedDirector()->getRunningScene();
    sec->addChild(layer);
    
    CCMenu *menu =CCMenu::create();
    CCMenuItemImage *itemImage =CCMenuItemImage::create("game_win.png", NULL, this, menu_selector(GameLayer::goNewGameSence));
    
    
    menu->addChild(itemImage);
    layer->addChild(menu);
}
void GameLayer::goNewGameSence()
{
//    GameScene *scenr=GameScene::createGameSence(++m_level);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1, GameScene::createGameSence(++m_level)));
    
}
