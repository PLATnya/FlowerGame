
#ifndef PROJ_ANDROID_PLAYER_H
#define PROJ_ANDROID_PLAYER_H
#include "cocos2d.h"
class Player {

    int coins = 150;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    int plantedFlowersCount = 0;
public:
    inline int GetCoins(){return coins;}
    Player();
    inline cocos2d::EventListenerTouchOneByOne* getTouchListener(){return touchListener;};
    void CheckListeners(cocos2d::Node *listenerNode);
    inline void AddCoins(int coins){this->coins+=coins;}
    inline int GetFlowersCount(){return plantedFlowersCount;}
    inline void AddFlower(){plantedFlowersCount++;}
};


#endif //PROJ_ANDROID_PLAYER_H
