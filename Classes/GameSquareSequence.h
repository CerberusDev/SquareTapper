// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareSequence : public GameSquare
{
protected:
	int NextSquareInSequenceIndex;
	bool bMyTurnToActivate;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquareSequence(cocos2d::Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate, const std::string& InactiveSpriteFilename);

	virtual void StartActivation(float ActivationTotalTime);
	virtual bool CanBeActivated() const { return GameSquare::CanBeActivated() && bMyTurnToActivate; };
	void SetNextSquareInSequenceIndex(int Index) { NextSquareInSequenceIndex = Index; };
	void SetAsNextToActivate() { bMyTurnToActivate = true; };
};
