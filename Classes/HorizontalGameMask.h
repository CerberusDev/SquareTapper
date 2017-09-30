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
	HorizontalGameMask(GameScene* argScene, bool bKillingMask);

protected:
	virtual void UpdateSpritePosition() override;
	virtual void Move() override;
	virtual void FrozeSquareActivation() override;
};
