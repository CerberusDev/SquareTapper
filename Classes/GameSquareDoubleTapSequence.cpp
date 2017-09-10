// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDoubleTapSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareDoubleTapSequence::GameSquareDoubleTapSequence(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/bgsqr_11_inactive_512.png", "img/squares/square_active_512.png"),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(argbMyTurnToActivate),
bAlreadyTapped(false)
{

}

void GameSquareDoubleTapSequence::StartActivation(float ActivationTotalTime)
{
	if (NextSquareInSequenceIndex != -1)
		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->SetNextSequenceSquareToActivate(NextSquareInSequenceIndex);

	GameSquare::StartActivation(ActivationTotalTime);
}

void GameSquareDoubleTapSequence::SquareCorrectlyTapped()
{
	if (bAlreadyTapped)
	{
		GameSquare::SquareCorrectlyTapped();
	}
	else
	{
		InactiveSprite->setTexture("img/squares/bgsqr_9_inactive_512.png");
		bAlreadyTapped = true;

		SetActivationFreeze(true);

		auto DelayAction = DelayTime::create(0.23f);
		auto UnfreezeFunc = CallFunc::create([&]() {
			SetActivationFreeze(false);
		});

		InactiveSprite->runAction(Sequence::create(DelayAction, UnfreezeFunc, nullptr));
	}
}
