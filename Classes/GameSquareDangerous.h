// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareDangerous : public GameSquare
{

// ---------------------------------------------------------------------------------------------------
public:
	GameSquareDangerous(cocos2d::Scene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);

protected:
	virtual void SquareCorrectlyTapped();
	virtual void ActivationEnded();
};
