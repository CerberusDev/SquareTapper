// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequence::GameSquareSequence(GameScene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/SquareSequence.png", "img/squares/SquareActive.png"),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(argbMyTurnToActivate)
{

}

void GameSquareSequence::StartActivation(float ActivationTotalTime)
{
	if (NextSquareInSequenceIndex != -1)
		ParentScene->SetNextSequenceSquareToActivate(NextSquareInSequenceIndex);

	GameSquare::StartActivation(ActivationTotalTime);
}
