// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameMask.h"

class ToggleGameMask : public GameMask
{
protected:
	cocos2d::Vec2 Position;
	cocos2d::Vec2 Size;
	bool bVisible;

// ---------------------------------------------------------------------------------------------------
public:
	ToggleGameMask(GameScene* argScene, bool bKillingMask, const cocos2d::Vec2& argPosition, const cocos2d::Vec2& argSize, bool bStartVisible = true);

protected:
	virtual void UpdateSpritePosition() override;
	virtual void Move() override;
	virtual void FrozeSquareActivation() override;
	virtual void OnFadingOutEnd() override;
};
