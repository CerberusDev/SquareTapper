// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

#define DESIGN_RES_X 720
#define DESIGN_RES_Y 1280

enum class ESquareState { Inactive, DuringActivation, Completed, Failed };

struct LevelParams
{
	int LevelDisplayNumber;
	int WorldNumber;
	int LevelNumber;
	int DangerousSquaresNumber;
	float SquaresActivationTimeInterval;
	float TotalSquareActivationTime;
	std::vector<int> DoubleTapSquareIndices;
	std::vector<int> SequenceSquareIndices;
	bool bSpawnGameMask;
	bool bVerticalMask;
	bool bKillingMask;

	LevelParams():
	LevelDisplayNumber(-1),
	WorldNumber(-1),
	LevelNumber(-1),
	DangerousSquaresNumber(-1),
	SquaresActivationTimeInterval(-1.0f), 
	TotalSquareActivationTime(-1.0f),
	bSpawnGameMask(false),
	bVerticalMask(false),
	bKillingMask(false)
	{};
};

std::string GetLevelRecordKey(const int LevelDisplayName);
std::string GetLevelAttemptsKey(const int LevelDisplayName);
