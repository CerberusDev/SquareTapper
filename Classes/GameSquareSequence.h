// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareSequence : public GameSquare
{
protected:
	static const std::string LineSpriteFilename;

	int NextSquareInSequenceIndex;
	bool bMyTurnToActivate;
	bool bAfterFirstActivation;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquareSequence(cocos2d::Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY);

	virtual void StartActivation(float ActivationTotalTime) override;

	virtual bool CanBeActivated() const override { return GameSquare::CanBeActivated() && (bMyTurnToActivate || bAfterFirstActivation); }
	void SetNextSquareInSequenceIndex(int Index) { NextSquareInSequenceIndex = Index; }
	void SetAsNextToActivate() { bMyTurnToActivate = true; }

protected:
	virtual void SafeActivationEnded() override;
};
