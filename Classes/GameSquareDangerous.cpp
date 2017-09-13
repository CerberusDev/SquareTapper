// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameSquareDangerous.h"
#include "GameScene.h"

USING_NS_CC;

GameSquareDangerous::GameSquareDangerous(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY) :
GameSquare(argScene, false, argSpritePosition, argPosX, argPosY, "img/squares/bgsqr_0_inactive_512.png", "img/squares/square_dangerous_main_512.png")
{

}

void GameSquareDangerous::SquareCorrectlyTapped()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);
	auto ScaleSequence = ScaleUpActivationSquare();
	Failed(ScaleSequence);
}

void GameSquareDangerous::ActivationEnded()
{
	State = ESquareState::Completed;

	ShowFinalSprites(false);

	if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
		ParentGameScene->OnSquareCompleted(this);
}
