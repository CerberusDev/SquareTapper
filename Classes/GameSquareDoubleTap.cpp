// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTap.h"

USING_NS_CC;

GameSquareDoubleTap::GameSquareDoubleTap(GameScene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/SquareDoubleTap.png"),
bAlreadyTapped(false)
{

}

void GameSquareDoubleTap::SquareCorrectlyTapped()
{
	if (bAlreadyTapped)
	{
		GameSquare::SquareCorrectlyTapped();
	}
	else
	{
		InactiveSprite->setTexture("img/squares/SquareInactive.png");

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);
		ActivationSprite->setScale(0.0f);
		StartActivation(SavedActivationTotalTime);

		bAlreadyTapped = true;
	}
}
