// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequence::GameSquareSequence(Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY, const std::string& InactiveSpriteFilename) :
GameSquare(argScene, bargDoubleTap, argSafetyType, argSpritePosition, argPosX, argPosY, InactiveSpriteFilename),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(false)
{

}

void GameSquareSequence::StartActivation(float ActivationTotalTime)
{
	if (NextSquareInSequenceIndex != -1)
		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->SetNextSequenceSquareToActivate(NextSquareInSequenceIndex);

	GameSquare::StartActivation(ActivationTotalTime);
}
