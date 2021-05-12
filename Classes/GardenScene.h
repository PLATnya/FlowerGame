
#ifndef __GARDENSCENE_SCENE_H__
#define __GARDENSCENE_SCENE_H__


#include "cocos2d.h"


class GardenScene : public cocos2d::Scene
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    int chunkWidth;

    cocos2d::Label* coinsLabel;
    cocos2d::Label* startLabel;

    std::vector<std::function<void(float)>> updateMethods;

public:

    void addUpdateMethod(const std::function<void(float)>& function);

    cocos2d::Sprite* makeFlower(const int& row, const int& column);

    cocos2d::Node* makeSnakeTail(const int& row, const int& column, const cocos2d::Color4F& tailColor, const cocos2d::Color4F& borderColor);

    cocos2d::Vec2 fromGridToPosition(const int& row, const int& column);
    std::pair<int,int> fromPositionToGrid(const cocos2d::Vec2& position);

    static GardenScene* createScene();
    virtual bool init();
    virtual void update(float delta);
    virtual void onExit();

    void drawGarden(const int& gardenWidth, const int& gardenHeight);
    void reloadCoins(const int& coins);
    void initLabels();
    void startLabels();


    inline const cocos2d::Vec2& getOrigin() const{return origin;}
    inline const cocos2d::Size& getVisibleSize() const{return visibleSize;}
    inline const int& getChunkWidth() const{return chunkWidth;}
    inline void setChunkWidth(const int& width){chunkWidth = visibleSize.width/width;}
    CREATE_FUNC(GardenScene);
};

#endif  //__GARDENSCENE_SCENE_H__
