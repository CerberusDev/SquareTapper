// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameScene;

class StarImage
{
protected:
	static const std::string StarImageFilePath_Active;
	static const std::string StarImageFilePath_Inactive;
	GameScene* ParentScene;
	cocos2d::Vec2 Position;

// ---------------------------------------------------------------------------------------------------
public:
	StarImage(GameScene* ParentScene, const cocos2d::Vec2& argPosition, const bool RecordSpriteActive);

	void Inactivate();
};
