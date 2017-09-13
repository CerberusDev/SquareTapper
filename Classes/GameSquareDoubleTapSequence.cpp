// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTapSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareDoubleTapSequence::GameSquareDoubleTapSequence(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquareSequence(argScene, true, argSpritePosition, argPosX, argPosY, argbMyTurnToActivate, "gui/bqsqr/bgsqr_11_inactive_512.png", "gui/squares/square_active_512.png")
{

}
