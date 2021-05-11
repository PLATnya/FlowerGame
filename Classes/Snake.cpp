

#include "Snake.h"

using namespace cocos2d;
void Snake::addTailPart() {
    auto last = *(tailParts.end()-1);
    Way& lastTailPartWayRef = GET_WAY(last);
    auto newGridPosition = step(GET_GRID(last),lastTailPartWayRef, true);
    auto tailPart = std::make_tuple(newGridPosition,garden->getScene()->makeSnakeTail(newGridPosition.first,newGridPosition.second), lastTailPartWayRef);
    tailParts.push_back(tailPart);
}

void Snake::removeTailPart() {

}

Snake::Snake(int row, int column, Way way, GardenModel* garden) {
    this->garden = garden;
    auto position = std::make_pair(row,column);

    tailParts.push_back(std::make_tuple(position, garden->getScene()->makeSnakeTail(row,column),way));
    garden->getScene()->addUpdateMethod([this](float delta){this->move(delta);});

    for(int i = 0;i<5;i++)addTailPart();

}

std::pair<int, int> Snake::step(std::pair<int,int> start, Way way, bool isInverse) {
    std::pair<int, int> stepWay = step(way,isInverse);
    return std::make_pair(start.first+stepWay.first,start.second+stepWay.second);
}

std::pair<int, int> Snake::step(Way way, bool isInverse) {
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
    return stepWay;
}

Way Snake::getNewWay(Way currentWay) {
    Way chooseArr[3];
    if(currentWay == LEFT||currentWay==RIGHT){
        chooseArr[0] = DOWN;
        chooseArr[1] = UP;
    }else{
        chooseArr[0] = LEFT;
        chooseArr[1] = RIGHT;
    }
    chooseArr[2] = currentWay;
    return chooseArr[cocos2d::RandomHelper::random_int(0,2)];
}

float t = 0;
int flips = 0;

void Snake::move(float delta) {
    if(t<speed){
        for(int i = 0;i<tailParts.size();++i) {
            auto stepDirect = step(GET_WAY(tailParts[i]));
            Vec2 direction = Vec2(stepDirect.first, stepDirect.second);
            GET_SPRITE(tailParts[i])->setPosition(GET_SPRITE(tailParts[i])->getPosition()
                                                  + direction * delta/speed *
                                                    garden->getScene()->getChunkWidth());
        }
        t+=delta;
    }else{
        Way& headWayRef = GET_WAY(tailParts[0]);
        Way buffWay = headWayRef;
        for(int i = 1;i<tailParts.size();++i) {
            Way& tailWayRef = GET_WAY(tailParts[i]);
            Way buff = tailWayRef;
            tailWayRef = buffWay;
            buffWay = buff;
        }
        recalculateMatrix();
        flips++;
        if(flips>=chunksCountToChangeWay) {
            headWayRef = getNewWay(headWayRef);
            flips = 0;
        }
        t = 0;
    }

}
void Snake::recalculateMatrix() {
    float width = garden->getScene()->getChunkWidth()/2;
    for(int i = 0;i<tailParts.size();++i){
        auto gridPosition = GET_GRID(tailParts[i]);
        GardenElement& gardenElementRef = garden->getGardenElementRef(gridPosition);
        gardenElementRef = DIRT;
        gridPosition = garden->getScene()->fromPositionToGrid(GET_SPRITE(tailParts[i])->getPosition()+Vec2(width,width));
        gardenElementRef = garden->getGardenElementRef(gridPosition);
        if(i==0) gardenElementRef = SNAKE_HEAD;
        else if(i==tailParts.size()-1) gardenElementRef = SNAKE_TAIL;
        else gardenElementRef = SNAKE_BODY;
    }
}
