// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameSquare;

class TutorialScene : public cocos2d::Scene
{
protected:
	GameSquare* Square;
	cocos2d::Size VisibleSize;

// ---------------------------------------------------------------------------------------------------

public:
	~TutorialScene();

	CREATE_FUNC(TutorialScene);

	virtual bool init();
};
