//
// Created by BOSS on 09.05.2021.
//

#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H
#include <vector>
#include <cocos2d.h>
#include "GardenModel.h"
enum Way {
    UP=0,
    DOWN,
    LEFT,
    RIGHT
};
class Snake {
    std::vector<std::tuple<std::pair<int,int>,cocos2d::Node*,Way>> tailParts;
    std::pair<int,int> step(std::pair<int,int> start, Way way, bool isInverse = false);
    std::pair<int,int> step(Way way, bool isInverse = false);

    GardenModel* garden;
public:
    Snake(int row, int column, Way way, GardenModel* garden);
    void addTailPart();
    void removeTailPart();




};


#endif //PROJ_ANDROID_SNAKE_H
