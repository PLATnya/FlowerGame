//
// Created by BOSS on 09.05.2021.
//

#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H
#include <vector>
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
    std::vector<std::tuple<int, int,cocos2d::Node&,Way>> tailParts;


    std::pair<int,int> step(int row, int column, Way way, bool isInverse = false);
    void stepByRef(int& row, int& column, Way way, bool isInverse = false);
    std::pair<int,int> step(Way way, bool isInverse = false);

    GardenModel* garden;
public:
    int speed =1;
    int chunksCountToChangeWay = 3;
    Snake(int row, int column, Way way, GardenModel* garden);
    void addTailPart();
    void removeTailPart();


    Way getNewWay(Way currentWay);


    void move(float delta);
};


#endif //PROJ_ANDROID_SNAKE_H
