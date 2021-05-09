
#include "GardenScene.h"
#include <algorithm>
USING_NS_CC;


void GardenScene::drawGarden(){

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gardenGrid = DrawNode::create();
    float borderWidth = 0.5f;
    float width = chunkWidth - borderWidth*2;
    for(int i = 0;i<kGardenHeight;++i) {
        for (int j = 0; j < kGardenWidth; ++j) {
            Vec2 origin = Vec2(j*chunkWidth +borderWidth, i*chunkWidth+borderWidth);
            Vec2 vertices[4] = { origin, origin + Vec2(width, 0), origin + Vec2(width, width), origin + Vec2(0, width) };
            gardenGrid->drawPolygon(vertices, 4, Color4F::GREEN,borderWidth,Color4F(101.0f/255.0f,167.0f/255.0f,33.0f/255.0f,1));
        }
    }

    addChild(gardenGrid);
    gardenGrid->setPosition(origin.x,origin.y);

}

Scene* GardenScene::createScene()
{
    return GardenScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GardenSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GardenScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    scheduleUpdate();
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    chunkWidth = visibleSize.width/kGardenWidth;


    gardenMatrix = new GardenElement*[kGardenHeight];
    for (int i = 0; i < kGardenHeight; ++i) {
        gardenMatrix[i] = new GardenElement[kGardenWidth];
        for (int j = 0; j < kGardenWidth; ++j) {
            gardenMatrix[i][j] = DIRT;
        }
    }
    gardener = new Player();
    drawGarden();
    gardener->getTouchListener()->onTouchBegan = [this](Touch* touch, Event* event) {

        plantFlower(convertTouchToNodeSpace(touch));
        return true;
    };
    gardener->checkListeners(this);



    coinsLabel = Label::createWithTTF("Coins:", "fonts/Marker Felt.ttf", 24);
    if (coinsLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {

        coinsLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - coinsLabel->getContentSize().height));
        this->addChild(coinsLabel, 1);
    }
    reloadCoins();
    return true;
}

float t = 0;
void GardenScene::update(float delta) {
    if(gardener->getFlowersCount() > 0) {
        if (t >= 3) {
            gardener->addCoins(gardener->getFlowersCount() * 5);
            reloadCoins();
            t = 0;
        } else t += delta;
    }
}


void GardenScene::onExit() {
    delete gardener;
    for(int i = 0;i<kGardenHeight;i++){
        delete[] gardenMatrix[i];
    }
    delete[] gardenMatrix;
    Node::onExit();
}

void GardenScene::plantFlower(cocos2d::Vec2 position) {
    log("FUCK %f", origin.y);
    if(gardener->getCoins() >= 50) {
        Vec2 bound(origin.x + chunkWidth * kGardenWidth, origin.y + chunkWidth * kGardenHeight);
        if (position.x < bound.x && position.y < bound.y) {
            gardener->addCoins(-50);
            gardener->addFlower();
            reloadCoins();
            Sprite *flower = Sprite::create("flower.png");

            Vec2 newPosition = position - origin;
            int row =(int)(newPosition.x/chunkWidth);
            int column =(int)(newPosition.y/chunkWidth);
            newPosition = Vec2(row+0.5f,column+0.5f)*chunkWidth + origin;


            flower->setPosition(newPosition);
            flower->setContentSize(Size(chunkWidth, chunkWidth));
            addChild(flower);
        }
    }
}

void GardenScene::reloadCoins() {
    std::stringstream ss;
    ss << "Coins: "<<std::to_string(gardener->getCoins());
    coinsLabel->setString(ss.str());
}
