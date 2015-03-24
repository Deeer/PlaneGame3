//
//  Cloud.h
//  PlaneGame
//
//  Created by METC on 15/3/24.
//
//

#ifndef __PlaneGame__Cloud__
#define __PlaneGame__Cloud__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Cloud:public CCSprite{
public:
    CREATE_FUNC(Cloud);
    bool init();
private:
    float m_speed;
    void move(float dt);
    void removeCloud();
    
    
};


#endif /* defined(__PlaneGame__Cloud__) */
