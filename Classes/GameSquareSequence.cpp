// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareSequence.h"
#include "GameScene.h"

USING_NS_CC;

const std::string GameSquareSequence::PlusSpriteFilename = "gui/bqsqr/bgsqr_straight_inactive_513.png";

GameSquareSequence::GameSquareSequence(BaseScene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, bargDoubleTap, argSafetyType, argSpritePosition, argPosX, argPosY),
NextSquareInSequenceIndex(-1),
bMyTurnToActivate(false),
bAfterFirstActivation(false)
{
	PlusSprite = Sprite::create(PlusSpriteFilename);
	PlusSprite->setPosition(SpritePosition);
	PlusSprite->setScale(SpritesScale);
	ParentScene->addChild(PlusSprite, 1);
}

GameSquareSequence::~GameSquareSequence()
{
	PlusSprite->removeFromParent();
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

	PlusSprite->setVisible(false);
}
