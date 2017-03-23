#pragma once

#include "cocos2d.h"

class GameScene;

class MySquare
{
protected:
	GameScene* ParentLayer;
	cocos2d::Sprite* MySprite;
	cocos2d::Sprite* MySecondSprite;
	cocos2d::Vec2 Position;
	bool bClickable;

	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);

public:
	MySquare(GameScene* argLayer, const cocos2d::Vec2& argPosition);
	void StartShowing();
};
