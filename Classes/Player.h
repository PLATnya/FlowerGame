
#ifndef PROJ_ANDROID_PLAYER_H
#define PROJ_ANDROID_PLAYER_H
#include "cocos2d.h"
class Player {

    int coins = 150;
    cocos2d::EventListenerTouchOneByOne* touchListener;
public:
    inline int GetCoins(){return coins;}
    Player();
    inline cocos2d::EventListenerTouchOneByOne* getTouchListener(){return touchListener;};
    void CheckListeners(cocos2d::Node *listenerNode);
};


#endif //PROJ_ANDROID_PLAYER_H
