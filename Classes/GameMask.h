// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;
class GameSquare;

class GameMask
{
protected:
	GameScene* ParentScene;
	cocos2d::EventListenerTouchOneByOne* EventListener;
	cocos2d::Sprite* MaskSprite;
	std::vector<GameSquare*> FrozenSquares;
	bool bKillOnTouch;
	bool bMaskFullyVisible;

// ---------------------------------------------------------------------------------------------------
public:
	GameMask(GameScene* argScene, std::string SpriteFilePath, bool bKillingMask);
	virtual ~GameMask();

	void OnGameOver();

protected:
	virtual void UpdateSpritePosition() = 0;
	virtual void Move() = 0;
	virtual void FrozeSquareActivation() = 0;
	void UnfrozeSquareActivation();
	void OnFadingInEnd();
	void OnFadingOutStart();
	void OnFadingOutEnd();
	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);
};
