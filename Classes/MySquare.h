#pragma once

#include "cocos2d.h"

class HelloWorld;

class MySquare
{
protected:
	HelloWorld* ParentLayer;
	cocos2d::Sprite* MySprite;
	cocos2d::Sprite* MySecondSprite;
	cocos2d::Vec2 Position;
	bool bClickable;

	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);

public:
	MySquare(HelloWorld* argLayer, const cocos2d::Vec2& argPosition);
	void StartShowing();
};
