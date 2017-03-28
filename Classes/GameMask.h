// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;

class GameMask
{
protected:
	GameScene* ParentScene;
	cocos2d::Sprite* MaskSprite;
	int StartIndex;

// ---------------------------------------------------------------------------------------------------
public:
	GameMask(GameScene* argScene);

protected:
	void UpdatePosition();
	void OnFadingOutEnd();
};
