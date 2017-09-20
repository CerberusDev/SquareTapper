// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "ui/CocosGUI.h"

class LevelSelectScene : public cocos2d::Scene
{
protected:
	static const std::string LevelButtonSpriteFilename_0Stars;
	static const std::string LevelButtonSpriteFilename_1Star;
	static const std::string LevelButtonSpriteFilename_2Stars;
	static const std::string LevelButtonSpriteFilename_3Stars;
	static const std::string LevelButtonSpriteFilename_Locked;

	static std::vector<std::vector<LevelParams>> LevelParamsContainer;
	int StartWorldNumber;
	int TotalNumberOfStars;

// ---------------------------------------------------------------------------------------------------

public:
	LevelSelectScene(int argStartWorldNumber);

	virtual bool init();

	static void InitializeLevelParams();
	static std::string GenerateFilenameForWorldConfig(int WorldNumber);
	static void InitializeLevelParamsForSingleWorld(const std::string& FilePath, int& TotalLevelNumber);
	static void AddSequenceSquareToLevelParams(LevelParams& CurrLevelParamsStruct, const std::string& SquareType, int SquareIndex);
	static const std::vector<std::vector<LevelParams>>& GetLevelData() { return LevelParamsContainer; };
	static LevelSelectScene* create(int argStartWorldNumber);
	static void GetNextLevelIDs(int CurrWorldNumber, int CurrLevelNumber, int& NextWorldNumber, int& NextLevelNumber);
	static void GetPrevLevelIDs(int CurrWorldNumber, int CurrLevelNumber, int& PrevWorldNumber, int& PrevLevelNumber);
	static bool IsNextLevelLocked(int CurrWorldNumber, int CurrLevelNumber);
	static void NotifyLevelCompleted(int CurrWorldNumber, int CurrLevelNumber, int NumberOfStars);

	void CreateLevelButton(int WorldNumber, int LevelNumber, cocos2d::ui::Layout* PageLayout);
	const std::string& GetLevelButtonSpriteFilename(int StarsNumber);
	void CreateWorldIcon(int WorldNumber, cocos2d::ui::Layout* PageLayout);
	void CreateTopArrowsIcons(int WorldNumber, cocos2d::ui::Layout* PageLayout);
	void CreateStarsLabel(cocos2d::ui::Layout* PageLayout);
	void CreateResetProgressButton();
	void CreateReloadScriptsButton();
	void CreateBackToMenuButton();
};
