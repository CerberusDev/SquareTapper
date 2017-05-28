// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class LevelSelectScene : public cocos2d::Scene
{
protected:
	std::vector<std::vector<LevelParams> > LevelParamsContainer;
	static const std::string UnknownLevelImageFilePath_Idle;
	static const std::string UnknownLevelImageFilePath_Pressed;
	int StartWorldNumber;

// ---------------------------------------------------------------------------------------------------

public:
	LevelSelectScene(int argStartWorldNumber);

	virtual bool init();

	static LevelSelectScene* create(int argStartWorldNumber);
};
