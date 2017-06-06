// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTap.h"

USING_NS_CC;

GameSquareDoubleTap::GameSquareDoubleTap(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/SquareDoubleTap.png", "img/squares/SquareActive.png"),
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
		bAlreadyTapped = true;

		SetActivationFreeze(true);

		auto DelayAction = DelayTime::create(0.23f);
		auto UnfreezeFunc = CallFunc::create([&]() { 
			SetActivationFreeze(false);
		});

		InactiveSprite->runAction(Sequence::create(DelayAction, UnfreezeFunc, nullptr));
	}
}
