
#ifndef __GARDENSCENE_SCENE_H__
#define __GARDENSCENE_SCENE_H__

#include "Player.h"
#include "cocos2d.h"


class GardenScene : public cocos2d::Scene
{
    const int kGardenWidth = 25;
    const int kGardenHeight = 7 ;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    int chunkWidth;

    enum GardenElement{
        DIRT,
        FLOWER
    };

    GardenElement** gardenMatrix;
    Player* gardener;
    cocos2d::Label* coinsLabel;

    void drawGarden();
    void reloadCoins();
    void plantFlower(cocos2d::Vec2 position);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float delta);
    virtual void onExit();

    CREATE_FUNC(GardenScene);
};

#endif // __GARDENSCENE_SCENE_H__
