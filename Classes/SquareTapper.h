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

enum class ESquareState { Inactive, DuringActivation, Completed, Failed };
enum class ESquareSafetyType { Safe, Standard, Dangerous };

struct LevelParams
{
	int LevelDisplayNumber;
	int WorldNumber;
	int LevelNumber;
	int DangerousSquaresNumber;
	int SafeSquaresNumber;
	float SquaresActivationTimeInterval;
	float TotalSquareActivationTime;
	std::vector<int> DoubleTapSquareIndices;
	std::vector<std::vector<int> > SequencesSquareIndices;
	std::vector<int> SequenceDoubleTapSquareIndices;
	bool bSpawnGameMask;
	bool bVerticalMask;
	bool bKillingMask;

	LevelParams():
	LevelDisplayNumber(-1),
	WorldNumber(-1),
	LevelNumber(-1),
	DangerousSquaresNumber(-1),
	SafeSquaresNumber(-1),
	SquaresActivationTimeInterval(-1.0f), 
	TotalSquareActivationTime(-1.0f),
	bSpawnGameMask(false),
	bVerticalMask(false),
	bKillingMask(false)
	{};
};

std::string GetLevelRecordKey(const int LevelDisplayName);
std::string GetLevelAttemptsKey(const int LevelDisplayName);
