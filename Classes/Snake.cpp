//
// Created by BOSS on 09.05.2021.
//

#include "Snake.h"

void Snake::addTailPart() {
    auto last = *(tailParts.end()-1);
    auto newGridPosition = step(std::get<0>(last),std::get<2>(last), true);
    tailParts.push_back(std::make_tuple(newGridPosition,scene->makeSnakeTail(newGridPosition.first,newGridPosition.second),std::get<2>(last)));
}

void Snake::removeTailPart() {

}

void Snake::recalculateMatrix() {

}

void Snake::move() {

}

Snake::Snake(int row, int column, Way way, GardenScene* scene) {
    this->scene = scene;
    tailParts.push_back(std::make_tuple(std::make_pair(row,column),scene->makeSnakeTail(row,column),way));
    addTailPart();
}

std::pair<int, int> Snake::step(std::pair<int,int> start, Way way, bool isInverse) {
    std::pair<int, int> stepWay(0,0);
    switch (way) {
        case Way::RIGHT:
            stepWay = std::make_pair(1,0);
            break;
        case Way::LEFT:
            stepWay = std::make_pair(-1,0);
            break;
        case Way::UP:
            stepWay = std::make_pair(0,1);
            break;
        case Way::DOWN:
            stepWay = std::make_pair(0,-1);
            break;
    }
    if(isInverse) stepWay = std::make_pair(-stepWay.first, -stepWay.second);
    return std::make_pair(start.first+stepWay.first,start.second+stepWay.second);
}
