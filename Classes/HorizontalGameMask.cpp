// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "HorizontalGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

HorizontalGameMask::HorizontalGameMask(GameScene* argScene, bool bKillingMask) :
GameMask(argScene, bKillingMask ? "Mask2.png" : "Mask4.png", bKillingMask),
CurrentRowIndex(0)
{
	UpdateSpritePosition();
}

void HorizontalGameMask::UpdateSpritePosition()
{
	float PosX = Director::getInstance()->getVisibleSize().width * 0.5f;
	MaskSprite->setPosition(PosX, ParentScene->GetScreenPositionY(CurrentRowIndex));
}

void HorizontalGameMask::Move()
{
	CurrentRowIndex = (++CurrentRowIndex % SQUARE_AMOUNT_Y);
}

void HorizontalGameMask::CoverSquares()
{
	auto Squares = ParentScene->GetSquares();

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		CoveredSquares.push_back(Squares[x][CurrentRowIndex]);
		Squares[x][CurrentRowIndex]->SetCoveredByMask(true);
	}
}
