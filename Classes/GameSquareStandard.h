// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareStandard : public GameSquare
{

// ---------------------------------------------------------------------------------------------------
public:
	GameSquareStandard(GameScene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);
};
