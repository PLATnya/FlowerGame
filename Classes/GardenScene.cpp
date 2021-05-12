
#include "GardenScene.h"
#include <algorithm>
USING_NS_CC;

void GardenScene::drawGarden(const int& gardenWidth, const int& gardenHeight){

    auto gardenGridNode = DrawNode::create();
    float borderWidth = 0.5f;
    float width = chunkWidth - borderWidth*2;
    for(int i = 0;i<gardenHeight;++i) {
        for (int j = 0; j < gardenWidth; ++j) {
            Vec2 chunkOrigin = Vec2(j * chunkWidth + borderWidth, i * chunkWidth + borderWidth);
            Vec2 vertices[4] = {chunkOrigin, chunkOrigin + Vec2(width, 0), chunkOrigin + Vec2(width, width), chunkOrigin + Vec2(0, width) };
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
    for(const auto& i: updateMethods){
        i(delta);
    }
}


void GardenScene::onExit() {

    Node::onExit();
}


void GardenScene::reloadCoins(const int& coins) {
    std::stringstream ss;
    ss << "Coins: "<<std::to_string(coins);
    coinsLabel->setString(ss.str());
}

Sprite* GardenScene::makeFlower(const int& row, const int& column) {
    Sprite *flower = Sprite::create("flower.png");


    Vec2 newPosition = fromGridToPosition(row, column) + Vec2(chunkWidth,chunkWidth)*0.5f;

    flower->setPosition(newPosition);
    flower->setContentSize(Size(chunkWidth, chunkWidth));
    addChild(flower);
    return flower;
}

void GardenScene::initLabels() {
    coinsLabel = Label::createWithTTF("Coins:", "fonts/Marker Felt.ttf", 24);

    coinsLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - coinsLabel->getContentSize().height));
    this->addChild(coinsLabel, 1);

    startLabel = Label::createWithTTF("Plant seed to start:", "fonts/Marker Felt.ttf", 24);
    startLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - startLabel->getContentSize().height*2));
    this->addChild(startLabel, 1);
}

void GardenScene::addUpdateMethod(const std::function<void(float)>& function) {
    updateMethods.push_back(function);
}


cocos2d::Node *GardenScene::makeSnakeTail(const int& row, const int& column, const cocos2d::Color4F& tailColor, const cocos2d::Color4F& borderColor) {
    auto tailNode = DrawNode::create();
    float borderWidth = 0.5f;
    Vec2 startOrigin = Vec2(1,1)*(borderWidth/2);
    float width = chunkWidth - borderWidth/2;

    Vec2 vertices[4] = { startOrigin, startOrigin + Vec2(width, 0), startOrigin + Vec2(width, width), startOrigin + Vec2(0, width) };
    tailNode->drawPolygon(vertices, 4, tailColor,borderWidth,borderColor);

    Vec2 newPosition = fromGridToPosition(row,column);

    tailNode->setPosition(newPosition);
    tailNode->setLocalZOrder(1);
    addChild(tailNode);
    return tailNode;
}

cocos2d::Vec2 GardenScene::fromGridToPosition(const int& row, const int& column) {
    return cocos2d::Vec2(row*chunkWidth,column*chunkWidth) + origin;
}

std::pair<int, int> GardenScene::fromPositionToGrid(const cocos2d::Vec2& position) {
    cocos2d::Vec2 newPosition = position - origin;
    int row =(int)(newPosition.x/chunkWidth);
    int column =(int)(newPosition.y/chunkWidth);
    return std::make_pair(row,column);
}



void GardenScene::startLabels() {
    startLabel->removeFromParentAndCleanup(true);
}
