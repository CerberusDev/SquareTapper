// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene) :
ParentScene(argScene),
MaskSprite(nullptr),
CurrentRowIndex(0)
{
	MaskSprite = Sprite::create("Mask1.png");
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 4);
	UpdatePosition();

	auto FadeInAction = FadeIn::create(0.15f);
	auto OnFadingInEndFunction = CallFunc::create([&]() { CoverSquares(); });
	auto DelayAction = DelayTime::create(2.0f);
	auto OnFadingOutStartFunction = CallFunc::create([&]() { UncoverSquares(); });
	auto FadeOutAction = FadeOut::create(0.15f);
	auto OnFadingOutEndFunction = CallFunc::create([&]() { OnFadingOutEnd(); });
	auto SequenceAction = Sequence::create(FadeInAction, OnFadingInEndFunction, DelayAction, OnFadingOutStartFunction, FadeOutAction, OnFadingOutEndFunction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));
}

void GameMask::UpdatePosition()
{
	float PosY = Director::getInstance()->getVisibleSize().height * 0.5f;
	MaskSprite->setPosition(ParentScene->GetScreenPositionX(CurrentRowIndex), PosY);
}

void GameMask::CoverSquares()
{
	auto Squares = ParentScene->GetSquares();

	for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
	{
		CoveredSquares.push_back(Squares[CurrentRowIndex][y]);
		Squares[CurrentRowIndex][y]->SetCoveredByMask(true);
	}
}

void GameMask::UncoverSquares()
{
	for (auto CurrSquare : CoveredSquares)
		CurrSquare->SetCoveredByMask(false);

	CoveredSquares.clear();
}


void GameMask::OnFadingOutEnd()
{
	CurrentRowIndex = (++CurrentRowIndex % SQUARE_AMOUNT_X);
	UpdatePosition();
}