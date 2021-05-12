
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
        auto gridPos = scene->fromPositionToGrid(position);

        if (position.x < bound.x && position.y < bound.y) {
            GardenElement touchedElement = gardenGrid->getGardenElementRef(gridPos.first,gridPos.second);
            if(touchedElement == DIRT){
                gardenGrid->addFlowerOnGrid(gridPos.first, gridPos.second);
            }else if(touchedElement == SNAKE_BODY || touchedElement == SNAKE_HEAD|| touchedElement == SNAKE_TAIL){
                gardenGrid->catchSnakeOnGrid(gridPos.first,gridPos.second);
            }

        }

        return true;
    };
    checkListeners(scene);
}

void Player::checkListeners(cocos2d::Node *listenerNode) {
    listenerNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,listenerNode);
}
