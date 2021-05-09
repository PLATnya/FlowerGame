/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GardenSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GardenScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    scheduleUpdate();
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    chunkWidth = visibleSize.width/kGardenWidth;
    /////////////////////////////

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

        PlantFlower(convertTouchToNodeSpace(touch));
        return true;
    };
    gardener->CheckListeners(this);



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
    ReloadCoins();
    return true;
}

float t = 0;
void GardenScene::update(float delta) {
    if(gardener->GetFlowersCount()>0) {
        if (t >= 3) {
            gardener->AddCoins(gardener->GetFlowersCount() * 5);
            ReloadCoins();
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

void GardenScene::PlantFlower(cocos2d::Vec2 position) {
    log("FUCK %f", origin.y);
    if(gardener->GetCoins()>=50) {
        Vec2 bound(origin.x + chunkWidth * kGardenWidth, origin.y + chunkWidth * kGardenHeight);
        if (position.x < bound.x && position.y < bound.y) {
            gardener->AddCoins(-50);
            gardener->AddFlower();
            ReloadCoins();
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

void GardenScene::ReloadCoins() {
    std::stringstream ss;
    ss << "Coins: "<<std::to_string(gardener->GetCoins());
    coinsLabel->setString(ss.str());
}
