// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequenceStandard.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequenceStandard::GameSquareSequenceStandard(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquareSequence(argScene, false, argSpritePosition, argPosX, argPosY, argbMyTurnToActivate, "img/squares/bgsqr_9_inactive_512.png", "img/squares/square_active_512.png")
{

}
