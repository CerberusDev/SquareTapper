// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquareSequence.h"

class GameSquareDoubleTapSequence : public GameSquareSequence
{
public:
	GameSquareDoubleTapSequence(cocos2d::Scene* argScene, const bool bargDangerous, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate);
};
