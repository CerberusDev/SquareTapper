// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTap.h"

USING_NS_CC;

GameSquareDoubleTap::GameSquareDoubleTap(Scene* argScene, const bool bargDangerous, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, true, bargDangerous, argSpritePosition, argPosX, argPosY, "gui/bqsqr/bgsqr_8_inactive_512.png", "gui/squares/square_active_512.png")
{

}
