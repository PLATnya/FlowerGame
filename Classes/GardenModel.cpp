
#include "GardenModel.h"

GardenModel::GardenModel(GardenScene* scene) {
    this->gardenScene = scene;
    gardenMatrix = new GardenElement*[kGardenHeight];
    for (int i = 0; i < kGardenHeight; ++i) {
        gardenMatrix[i] = new GardenElement[kGardenWidth];
        for (int j = 0; j < kGardenWidth; ++j) {
            gardenMatrix[i][j] = DIRT;
        }
    }

    getScene()->schedule([this](float t){
        addCoins(getFlowersCount() * 5);
        getScene()->reloadCoins(getCoins());
    },3,kRepeatForever,0,"Coins scheduler");

    gardenScene->setChunkWidth(kGardenWidth);
    gardenScene->initLabels();
    gardenScene->reloadCoins(150);
    gardenScene->drawGarden(kGardenWidth,kGardenHeight);
}

GardenModel::~GardenModel() {
    for(int i = 0;i<kGardenHeight;i++){
        delete[] gardenMatrix[i];
    }
    delete[] gardenMatrix;
}
#include "Snake.h"
void GardenModel::addFlowerOnGrid(const int& row, const int& column) {

    if (getCoins() >= 50 && gardenMatrix[column][row] == GardenElement::DIRT) {
        flowers.emplace_back(std::make_tuple(row, column, gardenScene->makeFlower(row, column)));
        addFlowers(1);
        addCoins(-50);
        getScene()->reloadCoins(getCoins());
        gardenMatrix[column][row] = GardenElement::FLOWER;
        startSpawning();
        if(flowers.size()>2) maxSnakeSize = 10; else maxSnakeSize = 5;
    }
}


void GardenModel::spawnSnake() {

    Way newWay = Way(random()%4);
    int newRow = cocos2d::RandomHelper::random_int(1,kGardenWidth-2);
    int newColumn = cocos2d::RandomHelper::random_int(1,kGardenHeight-2);
    auto tailPos = Snake::step(newRow, newColumn, newWay);
    if(getGardenElementRef(newRow,newColumn) == DIRT &&  getGardenElementRef(tailPos.first,tailPos.second) == DIRT)
        snakes.push_back(new Snake(newRow,newColumn,newWay,this));
}

void GardenModel::startSpawning() {
    if(!isSpawningStarted) {
        getScene()->startLabels();
        getScene()->schedule([this](float t) {
            spawnSnake();
        }, spawnTime, CC_REPEAT_FOREVER, 0, "spawn timer");
        getScene()->schedule([this](float t) {
            spawnTime -= spawnTime * 0.05f;
            getScene()->unschedule("spawn timer");
            getScene()->schedule([this](float t) { spawnSnake(); }, spawnTime, CC_REPEAT_FOREVER, 0,
                                 "spawn timer");
        }, 10, CC_REPEAT_FOREVER, 0, "reduce time");
        isSpawningStarted = true;
        spawnSnake();
    }
}

void GardenModel::catchSnakeOnGrid(const int& row, const int& column) {

    for(int i = 0;i<snakes.size();++i){
        if(snakes[i]->isPartIn(row, column)){
            snakes[i]->removeTailPart();
        }
    }
}

void GardenModel::eatFlowerOnGrid(const int &row, const int &column) {
    if(getGardenElementRef(row, column) == FLOWER){
            for (int i = 0;i<flowers.size();++i){
                decltype(auto) flower = flowers[i];
                if (GET_ROW(flower) == row && GET_COLUMN(flower) == column) {
                    addFlowers(-1);
                    cocos2d::Node *sprite = GET_SPRITE(flower);
                    flowers.erase(flowers.begin() + i);
                    sprite->removeFromParentAndCleanup(true);
                    getGardenElementRef(row, column) = DIRT;

                    auto bustAction = cocos2d::Sequence::create(
                            cocos2d::CallFunc::create([this]() { snakesSecondsPerChunk /= 2; }),
                            cocos2d::DelayTime::create(5),
                            cocos2d::CallFunc::create([this]() { snakesSecondsPerChunk *= 2; }),
                            NULL);
                    getScene()->runAction(bustAction);
                }
            }
    }
}

GardenElement &GardenModel::getGardenElementRef(int x, int y) const {
    if(x<kGardenWidth && y<kGardenHeight) return gardenMatrix[y][x];
    return gardenMatrix[0][0];
}

