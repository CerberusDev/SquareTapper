// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

class MySquare;

#define SQUARE_AMOUNT_X 3
#define SQUARE_AMOUNT_Y 5

class GameScene : public cocos2d::Scene
{
protected:
	MySquare* Squares[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y];
	std::vector<std::pair<int, int>> AvailableSquares;
	int LevelNumber;

// ---------------------------------------------------------------------------------------------------

public:
	GameScene();

    virtual bool init();
	virtual void onExit();
    
	static GameScene* create(int argLevelNumber);

	void ShowNextSquare();
};
