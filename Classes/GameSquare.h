// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;

class GameSquare
{
public:
	const int PosX;
	const int PosY;

protected:
	GameScene* ParentScene;
	cocos2d::Sprite* MySprite;
	cocos2d::Sprite* MySecondSprite;
	cocos2d::Vec2 SpritePosition;
	ESquareState State;
	bool bCoveredByMask;
	bool bPausedOnGameOver;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquare(GameScene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);

	void StartActivation(float ActivationTotalTime);
	void SetCoveredByMask(bool argbCoveredByMask);
	void PauseOnGameOver();

	ESquareState GetState() const { return State; }
	bool GetCoveredByMask() const { return bCoveredByMask; }

protected:
	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);
};
