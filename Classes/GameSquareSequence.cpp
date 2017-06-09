// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequence::GameSquareSequence(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/bgsqr_9_inactive_512.png", "img/squares/square_active_512.png"),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(argbMyTurnToActivate)
{

}

void GameSquareSequence::StartActivation(float ActivationTotalTime)
{
	if (NextSquareInSequenceIndex != -1)
		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->SetNextSequenceSquareToActivate(NextSquareInSequenceIndex);

	GameSquare::StartActivation(ActivationTotalTime);
}
