// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene, std::string SpriteFilePath) :
ParentScene(argScene),
MaskSprite(nullptr)
{
	MaskSprite = Sprite::create(SpriteFilePath);
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 3);

	auto FadeInAction = FadeIn::create(0.15f);
	auto OnFadingInEndFunction = CallFunc::create([&]() { CoverSquares(); });
	auto DelayAction = DelayTime::create(0.6f);
	auto OnFadingOutStartFunction = CallFunc::create([&]() { UncoverSquares(); });
	auto FadeOutAction = FadeOut::create(0.15f);
	auto OnFadingOutEndFunction = CallFunc::create([&]() { OnFadingOutEnd(); });
	auto SequenceAction = Sequence::create(FadeInAction, OnFadingInEndFunction, DelayAction, OnFadingOutStartFunction, FadeOutAction, OnFadingOutEndFunction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));
}

void GameMask::OnGameOver()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(MaskSprite);
}

void GameMask::UncoverSquares()
{
	for (auto CurrSquare : CoveredSquares)
		CurrSquare->SetCoveredByMask(false);

	CoveredSquares.clear();
}

void GameMask::OnFadingOutEnd()
{
	Move();
	UpdateSpritePosition();
}
