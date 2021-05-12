
#include "Snake.h"

using namespace cocos2d;
void Snake::addTailPart() {//TODO: tail on matrix
    if(tailParts.size()<garden->maxSnakeSize) {
        decltype(auto) last = *(tailParts.end() - 1);
        Way &lastTailPartWayRef = GET_WAY(last);
        int& lastTailRowRef = GET_ROW(last);
        int& lastTailColumnRef = GET_COLUMN(last);

        if(isGoodWay(lastTailRowRef, lastTailColumnRef, lastTailPartWayRef) ){
            auto newGridPosition = step(lastTailRowRef, lastTailColumnRef, lastTailPartWayRef, true);
            Node *newSprite = garden->getScene()->makeSnakeTail(newGridPosition.first,
                                                                newGridPosition.second, color,
                                                                Color4F::WHITE);

            auto forSprite = step(GET_WAY(last), true);
            Vec2 newSpritePosition = GET_SPRITE(last).getPosition() +
                                     Vec2(forSprite.first, forSprite.second) *
                                     garden->getScene()->getChunkWidth();
            newSprite->setPosition(newSpritePosition);
            tailParts.emplace_back(
                    std::tie(newGridPosition.first, newGridPosition.second, *newSprite,
                             lastTailPartWayRef));
        }
    }
}

void Snake::removeTailPart() {
    decltype(auto) tail = tailParts[tailParts.size()-1];
    Node& tailSprite = GET_SPRITE(tail);
    garden->getGardenElementRef(GET_ROW(tail), GET_COLUMN(tail)) = DIRT;
    tailParts.pop_back();
    tailSprite.removeFromParentAndCleanup(true);
}

Snake::Snake(int row, int column, Way way, GardenModel* garden) {
    this->garden = garden;
    color = Color4F(RandomHelper::random_int(0,255)/255.0f,
                    RandomHelper::random_int(0,255)/255.0f,
                    RandomHelper::random_int(0,255)/255.0f,1);

    tailParts.emplace_back(std::tie(row,column, *garden->getScene()->makeSnakeTail(row,column,color, Color4F::BLACK/2),way));
    garden->getScene()->addUpdateMethod([this](float delta){this->move(delta);});

    addTailPart();

    auto growingAction = Sequence::createWithTwoActions(DelayTime::create(3),CallFunc::create([this](){addTailPart();}));
    GET_SPRITE(tailParts[0]).runAction(RepeatForever::create(growingAction));

    timerBuffer =garden->snakesSecondsPerChunk;
}

std::pair<int, int>&& Snake::step(Way way, bool isInverse) {
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
    if(isInverse){
        stepWay.first*=-1;
        stepWay.second*=-1;
    }
    return std::move(stepWay);
}
void Snake::stepByRef(int& row, int& column, Way way, bool isInverse) {
    std::pair<int, int> stepWay = step(way,isInverse);
   row+=stepWay.first;
   column+=stepWay.second;
}

std::pair<int, int>&& Snake::step(int row, int column, Way way, bool isInverse) {
    std::pair<int, int> stepWay = step(way,isInverse);
    return std::move(std::make_pair(row+stepWay.first,column+stepWay.second));
}

Way* Snake::getNewWay(Way currentWay) {
    Way* chooseArr = new Way[3];
    if(currentWay == LEFT||currentWay==RIGHT){
        chooseArr[0] = DOWN;
        chooseArr[1] = UP;
    }else{
        chooseArr[0] = LEFT;
        chooseArr[1] = RIGHT;
    }
    chooseArr[2] = currentWay;
    return chooseArr;
}

void Snake::checkWay(Way& way, const int& row, const int& column) {
    stay = false;

    if(flipsBuffer < chunksCountToChangeWay&&isGoodWay(row, column, way)) {
        return;
    }
    Way* newWays = getNewWay(way);
    std::swap(newWays[RandomHelper::random_int(0,2)],newWays[RandomHelper::random_int(0,2)]);
    for(int i = 0;i<3;++i){
        if(isGoodWay(row, column, newWays[i])) {
            way = newWays[i];
            flipsBuffer = 0;
            delete newWays;
            return;
        }
    }
    delete newWays;
    stay = true;

}

void Snake::move(float delta) {
    if(timerBuffer<garden->snakesSecondsPerChunk){
        if(!stay) {
            for (int i = 0; i < tailParts.size(); ++i) {
                decltype(auto) tailPart = tailParts[i];
                auto stepDirect = step(GET_WAY(tailPart));
                Vec2 direction = Vec2(stepDirect.first, stepDirect.second);
                GET_SPRITE(tailPart).setPosition(GET_SPRITE(tailPart).getPosition()
                                                 +
                                                 direction * delta / garden->snakesSecondsPerChunk *
                                                 garden->getScene()->getChunkWidth());
            }
        }
        timerBuffer+=delta;
    }else{
        decltype(auto) headPart = tailParts[0];
        Way& headWayRef = GET_WAY(headPart);
        int& headRowRef = GET_ROW(headPart);
        int& headColumnRef = GET_COLUMN(headPart);
        //TODO: fix eating
        garden->eatFlowerOnGrid(headRowRef, headColumnRef);

        flipsBuffer++;
        Way buffWay = headWayRef;
        checkWay(headWayRef, headRowRef, headColumnRef);
        alignSnake();
        if(!stay) {

            garden->getGardenElementRef(headRowRef, headColumnRef) = DIRT;
            stepByRef(headRowRef, headColumnRef, headWayRef);//
            garden->getGardenElementRef(headRowRef, headColumnRef) = SNAKE_HEAD;
        }
        if(!stay) {
            for (int i = 1; i < tailParts.size(); ++i) {
                decltype(auto) tailPart = tailParts[i];

                Way &tailWayRef = GET_WAY(tailPart);

                Way buff = tailWayRef;
                tailWayRef = buffWay;
                buffWay = buff;

                int &tailRowRef = GET_ROW(tailPart);
                int &tailColumnRef = GET_COLUMN(tailPart);
                GardenElement newGardenElement;
                newGardenElement = SNAKE_BODY;
                if (i == tailParts.size() - 1) newGardenElement = SNAKE_TAIL;

                garden->getGardenElementRef(tailRowRef, tailColumnRef) = DIRT;
                stepByRef(tailRowRef, tailColumnRef, tailWayRef);//
                garden->getGardenElementRef(tailRowRef, tailColumnRef) = newGardenElement;
            }
        }
        timerBuffer = 0;
    }

}

void Snake::alignSnake() {
    for(int i = 0;i<tailParts.size();++i){
        decltype(auto) tailPart = tailParts[i];
        GET_SPRITE(tailPart).setPosition(garden->getScene()->fromGridToPosition(GET_ROW(tailPart),GET_COLUMN(tailPart)));
    }
}


bool Snake::isPartIn(const int& row, const int& column) {
    const GardenElement& element = garden->getGardenElementRef(row, column);
    switch (element) {
        case SNAKE_HEAD:
            if(GET_ROW(tailParts[0]) == row && GET_COLUMN(tailParts[0]) == column) return true;
            break;
        case SNAKE_TAIL:
            int tailIndex;
            tailIndex = tailParts.size()-1;
            if(GET_ROW(tailParts[tailIndex]) == row && GET_COLUMN(tailParts[tailIndex]) == column) return true;
            break;
        case SNAKE_BODY:
            for(int i = 1;i<tailParts.size()-1;++i)if(GET_ROW(tailParts[i]) == row && GET_COLUMN(tailParts[i]) == column) return true;
            break;
    }
    return false;
}

bool Snake::isGoodWay(const int& row, const int& column, const Way& way) {
        auto newGridPosition = step(row, column,way);
        if(newGridPosition.first>=0&&newGridPosition.second>=0&&
           newGridPosition.first<garden->kGardenWidth&&newGridPosition.second<garden->kGardenHeight) {
            GardenElement& elementRef = garden->getGardenElementRef(newGridPosition.first, newGridPosition.second);
            if (elementRef ==DIRT||elementRef == FLOWER)
                return true;
        }
        return false;
}
