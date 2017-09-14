// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareSequence::GameSquareSequence(Scene* argScene, const bool bargDoubleTap, const bool bargDangerous, const Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate, const std::string& InactiveSpriteFilename, const std::string& ActivationSpriteFilename) :
GameSquare(argScene, bargDoubleTap, bargDangerous, argSpritePosition, argPosX, argPosY, InactiveSpriteFilename, ActivationSpriteFilename),
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
