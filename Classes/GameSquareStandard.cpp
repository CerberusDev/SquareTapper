// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareStandard.h"

USING_NS_CC;

GameSquareStandard::GameSquareStandard(Scene* argScene, const bool bargDangerous, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, false, bargDangerous, argSpritePosition, argPosX, argPosY, "gui/bqsqr/bgsqr_0_inactive_512.png", "gui/squares/square_active_512.png")
{

}
