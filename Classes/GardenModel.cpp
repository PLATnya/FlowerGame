

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

void GardenModel::addFlowerOnGrid(const cocos2d::Vec2 position) {


    cocos2d::Vec2 origin = gardenScene->getOrigin();
    int chunkWidth = gardenScene->getChunkWidth();
    cocos2d::Vec2 newPosition = position - origin;
    int row =(int)(newPosition.x/chunkWidth);
    int column =(int)(newPosition.y/chunkWidth);

    cocos2d::Vec2 bound(origin.x + chunkWidth * kGardenWidth, origin.y + chunkWidth * kGardenHeight);
    if (position.x < bound.x && position.y < bound.y) {
        if (getCoins() >= 50) {
            gardenScene->makeFlower(row, column);
            addFlower();
            addCoins(-50);
            getScene()->reloadCoins(getCoins());
            gardenMatrix[column][row] = GardenElement::FLOWER;
        }
    }

}

