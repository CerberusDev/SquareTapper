// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

#define DESIGN_RES_X 720
#define DESIGN_RES_Y 1280

#define SQUARE_AMOUNT_X 3
#define SQUARE_AMOUNT_Y 5

#define BACKGROUND_COLOR Color3B(22, 16, 30)
#define GREY_COLOR Color3B(100, 96, 90)
#define GOLD_COLOR Color3B(247, 198, 70)

#define WORLD_NUMBER_ON_TUTORIAL_STANDARD 0
#define WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP 1

#define FONT_FILE_PATH_STANDARD "fonts/ADAM.CGPRO.ttf"

#define SQUARE_TEXTURES_SIZE 512.0f
#define BUTTON_TEXTURES_SIZE 512.0f
#define SQUARE_SPRITE_SIZE 160.0f
#define BUTTON_SPRITE_SIZE 100.0f
#define RECORD_SQUARE_SIZE 48.0f
#define STAR_SQUARE_SIZE 35.0f

enum class ESquareState { Inactive, DuringActivation, Completed, Failed };
enum class ESquareSafetyType { Safe, Standard, Dangerous, DangerousSecondTap };
enum class ETutorialType { StandardSquare, DoubleTapSquare };

struct LevelParams
{
	int LevelDisplayNumber;
	int WorldNumber;
	int LevelNumber;
	int SafeSquaresNumber;
	int DangerousSquaresNumber;
	int DangerousSecondTapSquaresNumber;
	float SquaresActivationTimeInterval;
	float TotalSquareActivationTime;
	std::vector<int> DoubleTapSquareIndices;
	std::vector<std::vector<int> > SequencesSquareIndices;
	std::vector<int> SequenceDoubleTapSquareIndices;
	bool bSpawnGameMask;
	bool bVerticalMask;
	bool bKillingMask;
	bool bLocked;

	LevelParams():
	LevelDisplayNumber(-1),
	WorldNumber(-1),
	LevelNumber(-1),
	SafeSquaresNumber(-1),
	DangerousSquaresNumber(-1),
	DangerousSecondTapSquaresNumber(-1),
	SquaresActivationTimeInterval(-1.0f), 
	TotalSquareActivationTime(-1.0f),
	bSpawnGameMask(false),
	bVerticalMask(false),
	bKillingMask(false),
	bLocked(true)
	{};
};

std::string GetLevelRecordKey(const int LevelDisplayName);
std::string GetLevelAttemptsKey(const int LevelDisplayName);

template<typename T>
bool VectorContains(const std::vector<T>& Vector, const T& ElementToCheck)
{
	return std::find(Vector.begin(), Vector.end(), ElementToCheck) != Vector.end();
}
