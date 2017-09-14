// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequenceStandard.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequenceStandard::GameSquareSequenceStandard(Scene* argScene, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquareSequence(argScene, false, argSafetyType, argSpritePosition, argPosX, argPosY, argbMyTurnToActivate, "gui/bqsqr/bgsqr_9_inactive_512.png")
{

}
