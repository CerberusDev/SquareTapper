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
	cocos2d::EventListenerTouchOneByOne* EventListener;
	cocos2d::Sprite* InactiveSprite;
	cocos2d::Sprite* ActivationSprite;
	cocos2d::Sprite* FailedSprite;
	cocos2d::Sprite* CompletedSprite;
	cocos2d::Vec2 SpritePosition;
	ESquareState State;
	float SavedActivationTotalTime;
	bool bActivationFrozen;
	bool bBlockTouchEvents;
	bool bPausedOnGameOver;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquare(GameScene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY, const std::string& InactiveSpriteFilename);
	virtual ~GameSquare();

	void StartActivation(float ActivationTotalTime);
	void SetActivationFreeze(bool argbActivationFrozen);
	void SetBlockTouchEvents(bool argbBlockTouchEvents);

	void PauseOnGameOver();

	bool CanBeActivated() const { return State == ESquareState::Inactive && !bActivationFrozen; }

protected:
	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void SquareCorrectlyTapped();
	void Failed();
};
