
#ifndef PROJ_ANDROID_PLAYER_H
#define PROJ_ANDROID_PLAYER_H
#include "cocos2d.h"
class Player {

    int coins = 150;
    int plantedFlowersCount = 0;

    cocos2d::EventListenerTouchOneByOne* touchListener;

public:

    Player();

    inline cocos2d::EventListenerTouchOneByOne* getTouchListener(){return touchListener;};
    void checkListeners(cocos2d::Node *listenerNode);

    inline int getCoins(){return coins;}
    inline void addCoins(int coins){ this->coins+=coins;}

    inline int getFlowersCount(){return plantedFlowersCount;}
    inline void addFlower(){plantedFlowersCount++;}
};


#endif //PROJ_ANDROID_PLAYER_H
