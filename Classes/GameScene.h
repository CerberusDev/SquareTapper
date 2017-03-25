// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#define COCOS2D_DEBUG 1
#define ACTIVATION_SEQUENCE_ACTION_TAG 1000

#include "cocos2d.h"

class MySquare;

#define SQUARE_AMOUNT_X 3
#define SQUARE_AMOUNT_Y 5

class GameScene : public cocos2d::Scene
{
protected:
	MySquare* Squares[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y];
	std::vector<MySquare*> AvailableSquares;
	const int LevelNumber;
	const float StartDelay;
	const float MaxTimeWithoutActiveSquare;
	const float TimeBetweenSquaresActivation;
	const float SquareActivationTotalTime;
	int ActiveSquaresNumber;

// ---------------------------------------------------------------------------------------------------

public:
	GameScene(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime);

    virtual bool init();
	virtual void onExit();
    
	static GameScene* create(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime);

	void ActivateNextSquare();
	void QueueNextSquareActivation(float Delay);
	void OnSquareCompleted();
	void OnSquareFailed();
};
