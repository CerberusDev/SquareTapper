// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "VerticalGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

VerticalGameMask::VerticalGameMask(GameScene* argScene, bool bKillingMask) :
GameMask(argScene, "Mask1.png", bKillingMask),
CurrentColumnIndex(0)
{
	UpdateSpritePosition();
}

void VerticalGameMask::UpdateSpritePosition()
{
	float PosY = Director::getInstance()->getVisibleSize().height * 0.5f;
	MaskSprite->setPosition(ParentScene->GetScreenPositionX(CurrentColumnIndex), PosY);
}

void VerticalGameMask::Move()
{
	CurrentColumnIndex = (++CurrentColumnIndex % SQUARE_AMOUNT_X);
}

void VerticalGameMask::CoverSquares()
{
	auto Squares = ParentScene->GetSquares();

	for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
	{
		CoveredSquares.push_back(Squares[CurrentColumnIndex][y]);
		Squares[CurrentColumnIndex][y]->SetCoveredByMask(true);
	}
}
