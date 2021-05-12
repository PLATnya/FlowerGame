
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

    bool stay = false;
    cocos2d::Color4F color;
    std::vector<std::tuple<int, int,cocos2d::Node&,Way>> tailParts;

    bool isGoodWay(const int& row, const int& column, const Way& way);

    static void stepByRef(int& row, int& column, Way way, bool isInverse = false);
    static std::pair<int,int>&& step(Way way, bool isInverse = false);
    static Way* getNewWay(Way currentWay);

    class GardenModel* garden;
public:

    static std::pair<int,int>&& step(const int& row, const int& column, const Way& way, bool isInverse = false);

    int chunksCountToChangeWay = 4;
    Snake(const int& row, const int& column, const Way& way, GardenModel* garden);
    void addTailPart();
    void removeTailPart(bool& isLast);

    void alignSnake();
    void move(float delta);

    void checkWay(Way& way, const int& row, const int& column);
    bool isPartIn(const int& row, const int& column);
};


#endif //PROJ_ANDROID_SNAKE_H
