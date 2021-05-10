
#ifndef PROJ_ANDROID_GARDENMODEL_H
#define PROJ_ANDROID_GARDENMODEL_H

#include "cocos2d.h"

#include "GardenScene.h"
enum GardenElement{
    DIRT,
    FLOWER
};
class GardenModel {


    GardenElement** gardenMatrix;
    GardenScene* gardenScene;

    int plantedFlowersCount = 0;
    int coins = 150;


    std::vector<cocos2d::Node*> flowers;
public:
    const int kGardenWidth = 25;
    const int kGardenHeight = 7 ;

    void addFlowerOnGrid(int row, int column);

    inline GardenScene* getScene(){return gardenScene;}


    inline int getFlowersCount(){return plantedFlowersCount;}
    inline void addFlower(){plantedFlowersCount++;}

    inline int getCoins(){return coins;}
    inline void addCoins(int coins){ this->coins+=coins;}

    GardenModel(GardenScene* scene);
    ~GardenModel();
};


#endif // PROJ_ANDROID_GARDENMODEL_H
