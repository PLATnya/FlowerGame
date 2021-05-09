
#include "Player.h"

Player::Player() {
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
}

void Player::checkListeners(cocos2d::Node *listenerNode) {
    listenerNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,listenerNode);
}
