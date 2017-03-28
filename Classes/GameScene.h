// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

#define ACTIVATION_SEQUENCE_ACTION_TAG 1000
#define SQUARE_AMOUNT_X 3
#define SQUARE_AMOUNT_Y 5

class GameSquare;
class GameMask;

class GameScene : public cocos2d::Scene
{
protected:
	GameSquare* Squares[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y];	
	GameMask* Mask;
	const int LevelNumber;
	const float StartDelay;
	const float MaxTimeWithoutActiveSquare;
	const float TimeBetweenSquaresActivation;
	const float SquareActivationTotalTime;
	const float SquarePositionMarginX;
	const float SquarePositionMarginY;
	cocos2d::Size VisibleSize;
	int ActiveSquaresNumber;
	int UnactivatedSquaresNumber;

// ---------------------------------------------------------------------------------------------------

public:
	GameScene(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime);

    virtual bool init();
	virtual void onExit();
    
	static GameScene* create(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime);

	float GetScreenPositionX(int SquareIndexX) const;
	float GetScreenPositionY(int SquareIndexY) const;
	GameSquare* GetSquareForActivation() const;
	void ActivateNextSquare();
	void QueueNextSquareActivation(float Delay);
	void OnSquareCompleted();
	void OnSquareFailed();

	GameSquare* (&GetSquares())[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y] { return Squares; }

protected:
	float GetScreenPosition(int SquareIndex, int SquareMax, float SquarePositionMargin, float ScreenSize) const;
};
