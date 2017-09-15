// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquareSequence.h"

class GameSquareSequenceStandard : public GameSquareSequence
{
public:
	GameSquareSequenceStandard(cocos2d::Scene* argScene, ESquareSafetyType argSafetyType, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);
};
