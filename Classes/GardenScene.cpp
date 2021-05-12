
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


    Vec2 newPosition = fromGridToPosition(row, column) + Vec2(chunkWidth,chunkWidth)*0.5f;

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


cocos2d::Node *GardenScene::makeSnakeTail(int row, int column, Color4F tailColor) {
    //TODO: snake unique border color and different color of snake head
    auto tailNode = DrawNode::create();
    float borderWidth = 0.5f;
    Vec2 startOrigin = Vec2(1,1)*(borderWidth/2);
    float width = chunkWidth - borderWidth/2;

    Vec2 vertices[4] = { startOrigin, startOrigin + Vec2(width, 0), startOrigin + Vec2(width, width), startOrigin + Vec2(0, width) };
    tailNode->drawPolygon(vertices, 4, tailColor,borderWidth,Color4F::WHITE);

    Vec2 newPosition = fromGridToPosition(row,column);

    tailNode->setPosition(newPosition);
    addChild(tailNode);
    return tailNode;
}

cocos2d::Vec2 GardenScene::fromGridToPosition(int row, int column) {
    return cocos2d::Vec2(row*chunkWidth,column*chunkWidth) + origin;
}

std::pair<int, int> GardenScene::fromPositionToGrid(const cocos2d::Vec2& position) {
    cocos2d::Vec2 newPosition = position - origin;
    int row =(int)(newPosition.x/chunkWidth);
    int column =(int)(newPosition.y/chunkWidth);
    return std::make_pair(row,column);
}
