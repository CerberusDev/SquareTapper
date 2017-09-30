// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "HorizontalGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

HorizontalGameMask::HorizontalGameMask(GameScene* argScene, bool bKillingMask, int InitialOffset) :
GameMask(argScene, bKillingMask),
CurrentRowIndex(InitialOffset)
{
	MaskSprite->setScaleX(((SQUARE_AMOUNT_X - 1) * GameScene::GetDistBetweenSquares() + SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);
	MaskSprite->setScaleY((SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);

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
