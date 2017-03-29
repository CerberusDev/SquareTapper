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

// ---------------------------------------------------------------------------------------------------
public:
	GameMask(GameScene* argScene, std::string SpriteFilePath);

	void OnGameOver();

protected:
	virtual void UpdateSpritePosition() = 0;
	virtual void Move() = 0;
	virtual void CoverSquares() = 0;
	void UncoverSquares();
	void OnFadingOutEnd();
};
