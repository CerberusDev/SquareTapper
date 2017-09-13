// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareDoubleTap : public GameSquare
{
public:
	GameSquareDoubleTap(cocos2d::Scene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);
};
