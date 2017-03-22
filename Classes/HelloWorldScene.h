#pragma once

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

class MySquare;

#define SQUARE_AMOUNT_X 3
#define SQUARE_AMOUNT_Y 5

class HelloWorld : public cocos2d::Layer
{
protected:
	MySquare* Squares[SQUARE_AMOUNT_X][SQUARE_AMOUNT_Y];
	std::vector<std::pair<int, int>> AvailableSquares;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onExit();
    
    CREATE_FUNC(HelloWorld);

	void ShowNextSquare();
};
