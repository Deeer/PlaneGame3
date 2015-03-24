//
//  MenuLayer.cpp
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "define.h"
#include "GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;


CCScene *  MenuLayer::scene()
{

    CCScene *scene= CCScene::create();
    MenuLayer *layer= MenuLayer::create();
    scene->addChild(layer);
    CCLog("creat");
    return scene;
}
bool MenuLayer::init()
{
      CCLog("init");
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))  return false;
    this->addLogo();
    return true;
}
void MenuLayer::addLogo()
{
    CCSprite *sprite =CCSprite::create(TarenaImageName);
    sprite->setPosition(SCREEN_CENTER);
    this->addChild(sprite);
    
    sprite->setOpacity(0);
    CCCallFunc *func =CCCallFunc::create(this, callfunc_selector(MenuLayer::addBackGround));
    CCFadeIn *fadein= CCFadeIn::create(1.4);
    CCDelayTime *time =CCDelayTime::create(1.0);
    CCFadeOut *fadeOut =CCFadeOut::create(1);
    CCSequence *seq= CCSequence::create(fadein,time,func,fadeOut,NULL);
    
    
    
    
    sprite->runAction(seq);
    
}
void MenuLayer::addBackGround(){
    CCSprite*bg =CCSprite::create(LogoImageName);
//    bg->setAnchorPoint(SCREEN_CENTER);
//    bg->setPosition(SCREEN_CENTER);
    bg->setAnchorPoint(CCPointZero);
    this->addChild(bg);

   
    
    CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(MenuLayer::addTitle));
//    CCMoveTo *moveTo =CCMoveTo::create(2.0, ccp(200, 200));
    CCFadeIn *fadeIn =CCFadeIn::create(1);
    CCMoveTo *moveTo =CCMoveTo::create(1, ccp(0, SCREEN.height-bg->getContentSize().height));
    CCSequence *sqe=CCSequence::create(fadeIn,moveTo,func,NULL);
    
//    CCSequence *seq2 =CCSequence::create(CCMoveTo::create(1, CCFadeIn::create(1),CCMoveTo::create(2, ccp(0, SCREEN.height-bg->getContentSize().height)),CCCallFunc::create(this, callfunc_selector(<#_SELECTOR#>))))

    bg->runAction(sqe);
}
void MenuLayer::addTitle()
{
    CCSprite *sprite =CCSprite::create(TitleImageName);
//    sprite->setVisible(<#bool bVisible#>)
//    sprite->setOpacity(0);
    this->addChild(sprite);
    sprite->setPosition(ccp(SCREEN.width*.5, 500));
//    CCMoveTo *moveTo =CCMoveTo::create(2, SCREEN_CENTER);
     CCMoveTo *moveTo =CCMoveTo::create(0.5, SCREEN_POSITION(0.5, 0.6));
//    CCFadeIn*fadeIn =CCFadeIn::create(1);
//    CCSpawn *spawn =CCSpawn::create(moveTo,fadeIn,NULL);
    CCEaseBackOut *backOut =CCEaseBackOut::create(moveTo);
 
//    CCCallFuncND *fucnND =CCCallFuncND::create(this, callfuncND_selector(MenuLayer::addMenu()), a)
    CCCallFunc *fun=CCCallFunc::create(this, callfunc_selector(MenuLayer::addMenu));
    CCSequence *seq =CCSequence::create(backOut,fun);
    sprite->runAction(seq);
 
  
}

void MenuLayer::addMenu()
{
    CCMenu *menu =CCMenu::create();
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(SCREEN_POSITION(0.5, 0.4));
//    menu->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(menu);
    CCLabelBMFont *label =CCLabelBMFont::create("Start","MyFont.fnt");
    CCMenuItemLabel *item =CCMenuItemLabel::create(label,this, menu_selector(MenuLayer::goGameSence));
    CCRotateBy *rotateBy =CCRotateBy::create(1, 3600);
    menu->setScale(0);
    CCScaleTo *scale =CCScaleTo::create(1, 1);
    CCSpawn*spaw= CCSpawn::create(rotateBy,scale,NULL);
    menu->runAction(spaw);
       menu->addChild(item);

};
void MenuLayer::goGameSence()
{

  
    
    SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
 CCScene*sence2= CCTransitionFlipX::create(1, GameScene::createGameSence(2),    kCCTransitionOrientationUpOver);
    CCDirector::sharedDirector()->replaceScene(sence2);
    
    
    
    
}




    
    
    



