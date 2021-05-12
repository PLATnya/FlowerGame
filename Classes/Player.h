
#ifndef PROJ_ANDROID_PLAYER_H
#define PROJ_ANDROID_PLAYER_H

#include "cocos2d.h"

#include "GardenModel.h"
class Player {

    cocos2d::EventListenerTouchOneByOne* touchListener;

    GardenModel* gardenGrid;
public:

    Player(GardenScene* scene);

    inline cocos2d::EventListenerTouchOneByOne* getTouchListener(){return touchListener;};
    void checkListeners(cocos2d::Node *listenerNode);

};


#endif // PROJ_ANDROID_PLAYER_H
