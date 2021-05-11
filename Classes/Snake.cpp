

#include "Snake.h"

using namespace cocos2d;
void Snake::addTailPart() {
    auto last = *(tailParts.end()-1);
    Way& lastTailPartWayRef = GET_WAY(last);
    auto newGridPosition = step(GET_ROW(last),GET_COLUMN(last),lastTailPartWayRef, true);
    auto tailPart = std::tie(newGridPosition.first,newGridPosition.second,*garden->getScene()->makeSnakeTail(newGridPosition.first,newGridPosition.second), lastTailPartWayRef);
    tailParts.push_back(tailPart);
}

void Snake::removeTailPart() {

}

Snake::Snake(int row, int column, Way way, GardenModel* garden) {
    this->garden = garden;

    tailParts.push_back(std::tie(row,column, *garden->getScene()->makeSnakeTail(row,column),way));
    garden->getScene()->addUpdateMethod([this](float delta){this->move(delta);});

    for(int i = 0;i<5;i++)addTailPart();

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
void Snake::stepByRef(int& row, int& column, Way way, bool isInverse) {
    std::pair<int, int> stepWay = step(way,isInverse);
   row+=stepWay.first;
   column+=stepWay.second;
}


std::pair<int, int> Snake::step(int row, int column, Way way, bool isInverse) {
    std::pair<int, int> stepWay = step(way,isInverse);
    return std::move(std::make_pair(row+stepWay.first,column+stepWay.second));
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
            GET_SPRITE(tailParts[i]).setPosition(GET_SPRITE(tailParts[i]).getPosition()
                                                  + direction * delta/speed *
                                                    garden->getScene()->getChunkWidth());
        }
        t+=delta;
    }else{
        Way& headWayRef = GET_WAY(tailParts[0]);
        Way buffWay = headWayRef;
        for(int i = 0;i<tailParts.size();++i) {
            decltype(auto) tailPart = tailParts[i];
            garden->getGardenElementRef(GET_ROW(tailPart),GET_COLUMN(tailPart)) = DIRT;
            stepByRef(GET_ROW(tailPart),GET_COLUMN(tailPart),GET_WAY(tailPart));
            GardenElement newGardenElement;

            if(i>0) {
                Way &tailWayRef = GET_WAY(tailPart);
                Way buff = tailWayRef;
                tailWayRef = buffWay;
                buffWay = buff;
                newGardenElement = SNAKE_BODY;
                if(i==tailParts.size()-1) newGardenElement = SNAKE_TAIL;
            }else newGardenElement = SNAKE_HEAD;
            garden->getGardenElementRef(GET_ROW(tailPart),GET_COLUMN(tailPart)) = newGardenElement;
        }

        flips++;
        if(flips>=chunksCountToChangeWay) {
            headWayRef = getNewWay(headWayRef);
            flips = 0;
        }
        t = 0;
    }

}
