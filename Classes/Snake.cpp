

#include "Snake.h"

void Snake::addTailPart() {
    auto last = *(tailParts.end()-1);
    auto newGridPosition = step(std::get<0>(last),std::get<2>(last), true);

    auto tailPart = std::make_tuple(newGridPosition,garden->getScene()->makeSnakeTail(newGridPosition.first,newGridPosition.second),std::get<2>(last));
    tailParts.push_back(tailPart);


    auto moveAction = cocos2d::MoveBy::create(1,[&tailPart,this](){
        auto gridOffset = step(std::get<2>(tailPart));
        return cocos2d::Vec2(gridOffset.first,gridOffset.second)*this->garden->getScene()->getChunkWidth();
    }());

    auto swapAction = cocos2d::CallFunc::create([&tailPart,&last, this](){
        std::get<0>(tailPart) = std::get<0>(last);
        std::get<2>(tailPart) = std::get<2>(last);
    });

    std::get<1>(tailPart)->runAction( cocos2d::RepeatForever::create(cocos2d::Sequence::create(moveAction, swapAction,
                                                                                                   nullptr)));
}

void Snake::removeTailPart() {

}



Snake::Snake(int row, int column, Way way, GardenModel* garden) {

    this->garden = garden;
    auto position = std::make_pair(row,column);

    tailParts.push_back(std::make_tuple(position, garden->getScene()->makeSnakeTail(row,column),way));


    auto moveAction = cocos2d::MoveBy::create(1,[this](){
        auto tailPart = tailParts[0];
        auto gridOffset = step(std::get<2>(tailPart));

       return cocos2d::Vec2(gridOffset.first,gridOffset.second)*this->garden->getScene()->getChunkWidth();
    }());

    auto swapAction = cocos2d::CallFunc::create([this](){
        auto tailPart = tailParts[0];
        std::get<0>(tailPart) = step(std::get<0>(tailPart),std::get<2>(tailPart));
    });

    std::get<1>(tailParts[0])->runAction( cocos2d::RepeatForever::create(cocos2d::Sequence::create(moveAction, swapAction,
                                                                                           nullptr)));

    addTailPart();

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
