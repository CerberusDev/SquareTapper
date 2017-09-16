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
	static const std::string ActivationSpriteFilename_Safe;
	static const std::string ActivationSpriteFilename_Standard;
	static const std::string ActivationSpriteFilename_Dangerous;
	static const std::string ActivationSpriteFilename_DangerousSecondTap;

	static const std::string InactiveSpriteFilename_Standard;
	static const std::string InactiveSpriteFilename_DoubleTap;

	static const std::string FailedSpriteFilename;
	static const std::string CompletedSpriteFilename;

	cocos2d::Scene* ParentScene;
	cocos2d::EventListenerTouchOneByOne* EventListener;
	cocos2d::Sprite* InactiveSprite;
	cocos2d::Sprite* ActivationSprite;
	cocos2d::Sprite* FailedSprite;
	cocos2d::Sprite* CompletedSprite;
	cocos2d::Vec2 SpritePosition;
	ESquareState State;
	ESquareSafetyType SafetyType;
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
	GameSquare(cocos2d::Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);
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
	void Completed(bool bUpscaleActivationSquare);
	void Failed(cocos2d::Sequence* ScaleUpSequence = nullptr);
	const std::string& GetActivationSpriteFilename(ESquareSafetyType argSafetyType);
};
