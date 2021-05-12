
#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H

#include <vector>
#include <tuple>
#include <cocos2d.h>
#include "GardenModel.h"


#define GET_COLUMN(__type__) std::get<1>(__type__)
#define GET_ROW(__type__) std::get<0>(__type__)
#define GET_WAY(__type__) std::get<3>(__type__)
#define GET_SPRITE(__type__) std::get<2>(__type__)

enum Way {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Snake {
    float timerBuffer = 0;
    int flipsBuffer = 0;

    cocos2d::Color4F color;
    std::vector<std::tuple<int, int,cocos2d::Node&,Way>> tailParts;

    static std::pair<int,int>&& step(int row, int column, Way way, bool isInverse = false);
    static void stepByRef(int& row, int& column, Way way, bool isInverse = false);
    static std::pair<int,int>&& step(Way way, bool isInverse = false);
    static Way getNewWay(Way currentWay);

    class GardenModel* garden;
public:

    float speed =1;

    int chunksCountToChangeWay = 2;
    Snake(int row, int column, Way way, GardenModel* garden);
    void addTailPart();
    void removeTailPart();

    void alignSnake();
    void move(float delta);

    bool isWayClear();

};


#endif //PROJ_ANDROID_SNAKE_H
