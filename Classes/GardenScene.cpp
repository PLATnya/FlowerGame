
#include "GardenScene.h"
#include <algorithm>
USING_NS_CC;


void GardenScene::drawGarden(int gardenWidth, int gardenHeight){

    auto gardenGridNode = DrawNode::create();
    float borderWidth = 0.5f;
    float width = chunkWidth - borderWidth*2;
    for(int i = 0;i<gardenHeight;++i) {
        for (int j = 0; j < gardenWidth; ++j) {
            Vec2 origin = Vec2(j*chunkWidth +borderWidth, i*chunkWidth+borderWidth);
            Vec2 vertices[4] = { origin, origin + Vec2(width, 0), origin + Vec2(width, width), origin + Vec2(0, width) };
            gardenGridNode->drawPolygon(vertices, 4, Color4F::GREEN,borderWidth,Color4F(101.0f/255.0f,167.0f/255.0f,33.0f/255.0f,1));
        }
    }
    addChild(gardenGridNode);
    gardenGridNode->setPosition(origin.x,origin.y);

}

GardenScene* GardenScene::createScene()
{
    return GardenScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GardenSceneScene.cpp\n");
}


bool GardenScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    scheduleUpdate();
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    return true;
}

void GardenScene::update(float delta) {
    for(auto i: updateMethods){
        i(delta);
    }
}


void GardenScene::onExit() {

    Node::onExit();
}


void GardenScene::reloadCoins(int coins) {
    std::stringstream ss;
    ss << "Coins: "<<std::to_string(coins);
    coinsLabel->setString(ss.str());
}

Sprite* GardenScene::makeFlower(int row, int column) {
    Sprite *flower = Sprite::create("flower.png");

    Vec2 newPosition = Vec2(row+0.5f,column+0.5f)*chunkWidth + origin;


    flower->setPosition(newPosition);
    flower->setContentSize(Size(chunkWidth, chunkWidth));
    addChild(flower);
    return flower;
}

void GardenScene::initCoins() {
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
}

void GardenScene::addUpdateMethod(std::function<void(float)> function) {
    updateMethods.push_back(function);
}
