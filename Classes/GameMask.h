// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;
class GameSquare;

#define MARGIN_SIZE 20.0f

class GameMask
{
protected:
	static const std::string StandardMaskSpriteFilename;
	static const std::string KillingMaskSpriteFilename;

	GameScene* ParentScene;
	cocos2d::EventListenerTouchOneByOne* EventListener;
	cocos2d::Sprite* MaskSprite;
	std::vector<GameSquare*> FrozenSquares;
	int FailedIconCounter;
	bool bKillOnTouch;
	bool bMaskFullyVisible;
	bool bShouldFinishAnimation;

// ---------------------------------------------------------------------------------------------------
public:
	GameMask(GameScene* argScene, bool bKillingMask);
	virtual ~GameMask();

	void RequestFinishAnimation() { bShouldFinishAnimation = true; }

protected:
	virtual void UpdateSpritePosition() = 0;
	virtual void Move() = 0;
	virtual void FrozeSquareActivation() = 0;
	void FinishAnimation();
	void UnfrozeSquareActivation();
	void OnFadingInEnd();
	void OnFadingOutStart();
	void OnFadingOutEnd();
	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);
};
