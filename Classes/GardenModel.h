
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

    float snakesSecondsPerChunk = 1;
    int maxSnakeSize = 5;

    const int kGardenWidth = 25;
    const int kGardenHeight = 7 ;

    void addFlowerOnGrid(const int& row, const int& column);
    void eatFlowerOnGrid(const int& row, const int& column);

    void startSpawning();


    inline GardenScene* getScene() const{return gardenScene;}
    GardenElement& getGardenElementRef(int x, int y) const;

    inline const int& getFlowersCount() const{return plantedFlowersCount;}
    inline void addFlowers(const int& count){plantedFlowersCount+=count;}

    inline const int& getCoins() const {return coins;}
    inline void addCoins(const int& coins){ this->coins+=coins;}

    GardenModel(GardenScene* scene);
    ~GardenModel();
};


#endif // PROJ_ANDROID_GARDENMODEL_H
