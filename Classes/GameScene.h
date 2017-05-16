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
	std::vector<GameSquare*> ActiveSquares;
	LevelParams LevelParamsStruct;
	const float StartDelay;
	const float MaxTimeWithoutActiveSquare;
	const float SquarePositionMarginX;
	const float SquarePositionMarginY;
	cocos2d::Size VisibleSize;
	int UnactivatedSquaresNumber;
	bool bLevelFinished;

// ---------------------------------------------------------------------------------------------------

public:
	GameScene(LevelParams argLevelParamsStruct);

    virtual bool init();
	virtual void onExit();
    
	static GameScene* create(LevelParams argLevelParamsStruct);

	float GetScreenPositionX(int SquareIndexX) const;
	float GetScreenPositionY(int SquareIndexY) const;
	GameSquare* GetSquareForActivation() const;
	void ActivateNextSquare();
	void QueueNextSquareActivation(float Delay);
	void OnSquareCompleted(GameSquare* CompletedSquare);
	void OnSquareFailed(GameSquare* FailedSquare);
	void LevelFailed();
	void LevelCompleted();
	void ShowLevelCompletedMessage();

	GameSquare* (&GetSquares())[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y] { return Squares; }

protected:
	float GetScreenPosition(int SquareIndex, int SquareMax, float SquarePositionMargin, float ScreenSize) const;
};
