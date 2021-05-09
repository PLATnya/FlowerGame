
#include "Player.h"
Player::Player(GardenScene* scene) {
    gardenGrid = new GardenModel(scene);
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    cocos2d::Vec2 origin = scene->getOrigin();

    int chunkWidth = gardenGrid->getScene()->getChunkWidth();
    cocos2d::Vec2 bound(origin.x + chunkWidth * gardenGrid->kGardenWidth, origin.y + chunkWidth * gardenGrid->kGardenHeight);


    touchListener->onTouchBegan = [this,scene,chunkWidth,origin,bound](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 position = scene->convertTouchToNodeSpace(touch);


        cocos2d::Vec2 newPosition = position - origin;
        int row =(int)(newPosition.x/chunkWidth);
        int column =(int)(newPosition.y/chunkWidth);

        if (position.x < bound.x && position.y < bound.y) {
            gardenGrid->addFlowerOnGrid(row, column);
        }

        return true;
    };
    checkListeners(scene);
}

void Player::checkListeners(cocos2d::Node *listenerNode) {
    listenerNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,listenerNode);
}
