// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTapSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareDoubleTapSequence::GameSquareDoubleTapSequence(Scene* argScene, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquareSequence(argScene, true, argSafetyType, argSpritePosition, argPosX, argPosY, "gui/bqsqr/bgsqr_11_inactive_512.png")
{

}
