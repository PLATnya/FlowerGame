
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
    gardenScene->initCoins();
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
void GardenModel::addFlowerOnGrid(int row, int column) {

    if (getCoins() >= 50 && gardenMatrix[column][row] == GardenElement::DIRT) {
        flowers.push_back(gardenScene->makeFlower(row, column));
        addFlower();
        addCoins(-50);
        getScene()->reloadCoins(getCoins());
        gardenMatrix[column][row] = GardenElement::FLOWER;
        startSpawning();
        if(flowers.size()>2) maxSnakSize = 10; else maxSnakSize = 5;
    }
}


void GardenModel::spawnSnake() {
    //TODO: check spawning place
        snakes.emplace_back(new Snake(cocos2d::RandomHelper::random_int(1,kGardenWidth-2),
                                      cocos2d::RandomHelper::random_int(1,kGardenHeight-2),
                                      Way(rand()%4),this));
}

void GardenModel::startSpawning() {
    if(!isSpawningStarted) {
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

