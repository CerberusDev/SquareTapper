// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

const std::string GameSquareSequence::LineSpriteFilename = "gui/bqsqr/bgsqr_straight_inactive_512.png";

GameSquareSequence::GameSquareSequence(Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, bargDoubleTap, argSafetyType, argSpritePosition, argPosX, argPosY),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(false),
bAfterFirstActivation(false)
{
	auto LineSprite = Sprite::create(LineSpriteFilename);
	LineSprite->setPosition(SpritePosition);
	LineSprite->setScale(SpritesScale);
	ParentScene->addChild(LineSprite, 1);

	auto LineSprite2 = Sprite::create(LineSpriteFilename);
	LineSprite2->setPosition(SpritePosition);
	LineSprite2->setScale(SpritesScale);
	LineSprite2->setRotation(90.0f);
	ParentScene->addChild(LineSprite2, 1);
}

void GameSquareSequence::StartActivation(float ActivationTotalTime)
{
	if (!bAfterFirstActivation && NextSquareInSequenceIndex != -1)
		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->SetNextSequenceSquareToActivate(NextSquareInSequenceIndex);

	bAfterFirstActivation = true;

	GameSquare::StartActivation(ActivationTotalTime);
}

void GameSquareSequence::SafeActivationEnded()
{
	GameSquare::SafeActivationEnded();
}
