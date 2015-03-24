//
//  define.h
//  PlaneGame
//
//  Created by METC on 15/3/23.
//
//

#ifndef PlaneGame_define_h
#define PlaneGame_define_h
#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define SCREEN_CENTER ccp(SCREEN.width*.5, SCREEN.height*.5)
#define TarenaImageName "Menu/tarena.jpg"
#define LogoImageName "Menu/img_bg_logo.jpg"
#define TitleImageName "Menu/LOGO.png"
#define SCREEN_POSITION(_x,_y) ccp(SCREEN.width*(_x),SCREEN.height*(_y))
#define Menuimage "Menu/Menu.png"
#endif
