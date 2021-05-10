//
// Created by BOSS on 09.05.2021.
//

#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H
#include <vector>
#include <cocos2d.h>
#include "GardenScene.h"
enum Way {
    UP=0,
    DOWN,
    LEFT,
    RIGHT
};
class Snake {
    std::vector<std::tuple<std::pair<int,int>,cocos2d::Node*,Way>> tailParts;
    std::pair<int,int> step(std::pair<int,int> start, Way way, bool isInverse = false);

    GardenScene* scene;
public:
    Snake(int row, int column, Way way, GardenScene* scene);
    void addTailPart();
    void removeTailPart();

    void recalculateMatrix();
    void move();


};


#endif //PROJ_ANDROID_SNAKE_H
