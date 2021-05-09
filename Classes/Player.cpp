
#include "Player.h"
Player::Player(cocos2d::Scene* scene) {
    gardenGrid = new GardenModel(dynamic_cast<GardenScene*>(scene));
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this,scene](cocos2d::Touch* touch, cocos2d::Event* event) {
        gardenGrid->addFlowerOnGrid(scene->convertTouchToNodeSpace(touch));
        return true;
    };
    checkListeners(scene);
}

void Player::checkListeners(cocos2d::Node *listenerNode) {
    listenerNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,listenerNode);
}
