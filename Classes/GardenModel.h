
#ifndef PROJ_ANDROID_GARDENMODEL_H
#define PROJ_ANDROID_GARDENMODEL_H

#include "cocos2d.h"

#include "GardenScene.h"
#include "Snake.h"

enum GardenElement{
    DIRT,
    FLOWER,
    SNAKE_HEAD,
    SNAKE_BODY,
    SNAKE_TAIL
};
class GardenModel {

    bool isSpawningStarted = false;
    float spawnTime = 5;


    GardenElement** gardenMatrix;
    GardenScene* gardenScene;

    int plantedFlowersCount = 0;
    int coins = 150;

    std::vector<class Snake*> snakes;
    std::vector<std::tuple<int, int, cocos2d::Node*>> flowers;

    void spawnSnake();
public:

    void catchSnakeOnGrid(const int& row, const int& column);

    int maxSnakSize = 5;

    const int kGardenWidth = 25;
    const int kGardenHeight = 7 ;

    void addFlowerOnGrid(int row, int column);
    void eatFlowerOnGrid(const int& row, const int& column);

    void startSpawning();


    inline GardenScene* getScene(){return gardenScene;}

    inline GardenElement& getGardenElementRef(int x, int y){return gardenMatrix[y][x];}

    inline int getFlowersCount(){return plantedFlowersCount;}
    inline void addFlowers(int count){plantedFlowersCount+=count;}

    inline int getCoins(){return coins;}
    inline void addCoins(int coins){ this->coins+=coins;}

    GardenModel(GardenScene* scene);
    ~GardenModel();
};


#endif // PROJ_ANDROID_GARDENMODEL_H
