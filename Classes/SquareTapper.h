// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

enum class ESquareState { Inactive, DuringActivation, Completed, Failed };

struct LevelParams
{
	int LevelNumber;
	float SquaresActivationTimeInterval;
	float TotalSquareActivationTime;
	bool bSpawnGameMask;
	bool bVerticalMask;
	bool bKillingMask;

	LevelParams():
	LevelNumber(-1), 
	SquaresActivationTimeInterval(-1.0f), 
	TotalSquareActivationTime(-1.0f),
	bSpawnGameMask(false),
	bVerticalMask(false),
	bKillingMask(false)
	{};
};
