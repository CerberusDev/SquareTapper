// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "ToggleGameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

ToggleGameMask::ToggleGameMask(GameScene* argScene, bool bKillingMask, const Vec2& argPosition, const Vec2& argSize, bool bStartVisible) :
GameMask(argScene, bKillingMask),
Position(argPosition),
Size(argSize),
bVisible(bStartVisible)
{
	MaskSprite->setScaleX(((Size.x - 1) * GameScene::GetDistBetweenSquares() + SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);
	MaskSprite->setScaleY(((Size.y - 1) * GameScene::GetDistBetweenSquares() + SQUARE_SPRITE_SIZE + 2.0f * MARGIN_SIZE) / SQUARE_TEXTURES_SIZE);

	UpdateSpritePosition();

	if (bVisible)
		FrozeSquareActivation();
	else
		MaskSprite->setVisible(false);
}

void ToggleGameMask::UpdateSpritePosition()
{
	float PosX = (GameScene::GetScreenPositionX(Position.x) + GameScene::GetScreenPositionX(Position.x + Size.x - 1)) / 2.0f;
	float PosY = (GameScene::GetScreenPositionY(Position.y) + GameScene::GetScreenPositionY(Position.y + Size.y - 1)) / 2.0f;

	MaskSprite->setPosition(PosX, PosY);
}

void ToggleGameMask::Move()
{
	// do not move!
}

void ToggleGameMask::FrozeSquareActivation()
{
	auto Squares = ParentScene->GetSquares();

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
		{
			if (x >= Position.x && x < Position.x + Size.x && y >= Position.y && y < Position.y + Size.y)
			{
				FrozenSquares.push_back(Squares[x][y]);
				Squares[x][y]->SetActivationFreeze(true);
			}
		}
	}
}

void ToggleGameMask::OnFadingOutEnd()
{
	bVisible = !bVisible;
	MaskSprite->setVisible(bVisible);

	if (bVisible)
		FrozeSquareActivation();
	else
		UnfrozeSquareActivation();
}