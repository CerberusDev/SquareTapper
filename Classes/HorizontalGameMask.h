// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameMask.h"

class HorizontalGameMask : public GameMask
{
protected:
	int CurrentRowIndex;

// ---------------------------------------------------------------------------------------------------
public:
	HorizontalGameMask(GameScene* argScene);

protected:
	virtual void UpdateSpritePosition();
	virtual void Move();
	virtual void CoverSquares();
};
