//
// Created by BOSS on 09.05.2021.
//

#ifndef PROJ_ANDROID_SNAKE_H
#define PROJ_ANDROID_SNAKE_H
#include <vector>
#include <cocos2d.h>

class Snake {
    std::vector<std::pair<int,int>> tailCoords;
    std::vector<cocos2d::Node> tailNodes;
public:
    Snake();
    void addTailPart();
    void removeTailPart();

    void recalculateMatrix();
    void move();
};


#endif //PROJ_ANDROID_SNAKE_H
