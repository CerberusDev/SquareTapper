// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "VerticalGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

VerticalGameMask::VerticalGameMask(GameScene* argScene, bool bKillingMask) :
GameMask(argScene, bKillingMask),
CurrentColumnIndex(0)
{
	MaskSprite->setScaleX((SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);
	MaskSprite->setScaleY(((SQUARE_AMOUNT_Y - 1) * GameScene::GetDistBetweenSquares() + SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);

	UpdateSpritePosition();
	FrozeSquareActivation();
}

void VerticalGameMask::UpdateSpritePosition()
{
	MaskSprite->setPosition(GameScene::GetScreenPositionX(CurrentColumnIndex), GameScene::GetScreenPositionY(2));
}

void VerticalGameMask::Move()
{
	CurrentColumnIndex = (++CurrentColumnIndex % SQUARE_AMOUNT_X);
}

void VerticalGameMask::FrozeSquareActivation()
{
	auto Squares = ParentScene->GetSquares();

	for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
	{
		FrozenSquares.push_back(Squares[CurrentColumnIndex][y]);
		Squares[CurrentColumnIndex][y]->SetActivationFreeze(true);
	}
}
