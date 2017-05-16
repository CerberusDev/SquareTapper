// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;

class StarImage
{
protected:
	cocos2d::Sprite* ActiveSprite;
	cocos2d::Sprite* InactiveSprite;

// ---------------------------------------------------------------------------------------------------
public:
	StarImage(GameScene* ParentScene, const cocos2d::Vec2& Position);

	void Inactivate();
};
