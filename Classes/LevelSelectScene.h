// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class LevelSelectScene : public cocos2d::Scene
{
protected:
	std::vector<LevelParams> LevelParamsContainer;

public:
	virtual bool init();

	CREATE_FUNC(LevelSelectScene);
};
