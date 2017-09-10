// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "GameSquare.h"

class GameSquareDoubleTapSequence : public GameSquare
{
public:
	int NextSquareInSequenceIndex;
	bool bMyTurnToActivate;

protected:
	bool bAlreadyTapped;

// ---------------------------------------------------------------------------------------------------
public:
	GameSquareDoubleTapSequence(cocos2d::Scene* argScene, const cocos2d::Vec2& argSpritePosition, int argPosX, int argPosY, bool argbMyTurnToActivate);

	virtual void StartActivation(float ActivationTotalTime);
	virtual bool CanBeActivated() const { return GameSquare::CanBeActivated() && bMyTurnToActivate; };
	void SetNextSquareInSequenceIndex(int Index) { NextSquareInSequenceIndex = Index; };
	void SetAsNextToActivate() { bMyTurnToActivate = true; };

protected:
	virtual void SquareCorrectlyTapped();
};
