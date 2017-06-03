// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDangerous.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareDangerous::GameSquareDangerous(GameScene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, argSpritePosition, argPosX, argPosY, "img/squares/SquareInactive.png", "img/squares/SquareDangerous.png")
{

}

void GameSquareDangerous::SquareCorrectlyTapped()
{
	Failed();
	ScaleUpActivationSquare();
}

void GameSquareDangerous::ActivationEnded()
{
	State = ESquareState::Completed;

	CompletedSprite = Sprite::create("img/squares/SquareCompleted.png");
	CompletedSprite->setPosition(SpritePosition);
	CompletedSprite->setOpacity(0.0f);
	ParentScene->addChild(CompletedSprite, 3);

	auto FadeInAction = FadeIn::create(CompletedSpriteFadeInTime);
	CompletedSprite->runAction(FadeInAction);

	ParentScene->OnSquareCompleted(this);
}
