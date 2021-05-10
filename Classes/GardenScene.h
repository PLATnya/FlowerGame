
#ifndef __GARDENSCENE_SCENE_H__
#define __GARDENSCENE_SCENE_H__


#include "cocos2d.h"


class GardenScene : public cocos2d::Scene
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    int chunkWidth;


    cocos2d::Label* coinsLabel;

    std::vector<std::function<void(float)>> updateMethods;

public:

    void addUpdateMethod(std::function<void(float)> function);

    cocos2d::Sprite* makeFlower(int row, int column);

    cocos2d::Node* makeSnakeTail(int row, int column);

    cocos2d::Vec2 fromGridToPosition(int row, int column);
    std::pair<int,int> fromPositionToGrid(const cocos2d::Vec2& position);

    static GardenScene* createScene();
    virtual bool init();
    virtual void update(float delta);
    virtual void onExit();

    void drawGarden(int gardenWidth, int gardenHeight);
    void reloadCoins(int coins);
    void initCoins();

    inline void up(float t){}

    inline cocos2d::Vec2& getOrigin(){return origin;}
    inline cocos2d::Size& getVisibleSize(){return visibleSize;}
    inline int getChunkWidth(){return chunkWidth;}
    inline void setChunkWidth(int width){chunkWidth = visibleSize.width/width;}
    CREATE_FUNC(GardenScene);
};

#endif  //__GARDENSCENE_SCENE_H__
