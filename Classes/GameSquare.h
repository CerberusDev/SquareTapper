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
	cocos2d::Scene* ParentScene;
	cocos2d::EventListenerTouchOneByOne* EventListener;
	cocos2d::Sprite* InactiveSprite;
	cocos2d::Sprite* ActivationSprite;
	cocos2d::Sprite* FailedSprite;
	cocos2d::Sprite* CompletedSprite;
	cocos2d::Vec2 SpritePosition;
	ESquareState State;
	float SavedActivationTotalTime;
	const float CompletedSpriteFadeInTime;
	const float SpritesScale;
	int ActivationFreezeRequestsCounter;
	const bool bDoubleTap;
	bool bAlreadyTapped;
	bool bBlockTouchEvents;
	bool bPausedOnGameOver;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquare(cocos2d::Scene* argScene, const bool bargDoubleTap, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY, const std::string& InactiveSpriteFilename, const std::string& ActivationSpriteFilename);
	virtual ~GameSquare();

	virtual void StartActivation(float ActivationTotalTime);
	void SetActivationFreeze(bool argbActivationFrozen);
	void SetBlockTouchEvents(bool argbBlockTouchEvents);
	void SimulateCorrectTap();
	void PauseOnGameOver();

	virtual bool CanBeActivated() const { return State == ESquareState::Inactive && ActivationFreezeRequestsCounter == 0; }

protected:
	void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void SquareCorrectlyTapped();
	virtual void ActivationEnded();
	void ShowFinalSprites(bool bShowFailedSprite, cocos2d::Sequence* ScaleUpSequence = nullptr);
	cocos2d::Sequence* ScaleUpActivationSquare();
	void Failed(cocos2d::Sequence* ScaleUpSequence = nullptr);
};
