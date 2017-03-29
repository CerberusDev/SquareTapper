// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;
class GameSquare;

class GameMask
{
protected:
	GameScene* ParentScene;
	cocos2d::Sprite* MaskSprite;
	std::vector<GameSquare*> CoveredSquares;
	int CurrentRowIndex;

// ---------------------------------------------------------------------------------------------------
public:
	GameMask(GameScene* argScene);

	void OnGameOver();

protected:
	void UpdatePosition();
	void CoverSquares();
	void UncoverSquares();
	void OnFadingOutEnd();
};
