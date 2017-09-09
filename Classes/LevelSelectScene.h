// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class LevelSelectScene : public cocos2d::Scene
{
protected:
	static std::vector<std::vector<LevelParams>> LevelParamsContainer;
	int StartWorldNumber;

// ---------------------------------------------------------------------------------------------------

public:
	LevelSelectScene(int argStartWorldNumber);

	virtual bool init();

	static void InitializeLevelParams();
	static void InitializeLevelParamsForSingleWorld(const std::string& FilePath, int& TotalLevelNumber);
	static void AddSequenceSquareToLevelParams(LevelParams& CurrLevelParamsStruct, const std::string& SquareType, int SquareIndex);
	static const std::vector<std::vector<LevelParams>>& GetLevelData() { return LevelParamsContainer; };
	static LevelSelectScene* create(int argStartWorldNumber);
};
