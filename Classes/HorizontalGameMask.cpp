// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "HorizontalGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

HorizontalGameMask::HorizontalGameMask(GameScene* argScene, bool bKillingMask) :
GameMask(argScene, bKillingMask ? "img/masks/Mask2.png" : "img/masks/Mask4.png", bKillingMask),
CurrentRowIndex(0)
{
	UpdateSpritePosition();
	FrozeSquareActivation();
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

void HorizontalGameMask::FrozeSquareActivation()
{
	auto Squares = ParentScene->GetSquares();

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		FrozenSquares.push_back(Squares[x][CurrentRowIndex]);
		Squares[x][CurrentRowIndex]->SetActivationFreeze(true);
	}
}
