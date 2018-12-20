// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class BaseScene : public cocos2d::Scene
{
// ---------------------------------------------------------------------------------------------------

public:
	virtual void OnSquareCompleted(class GameSquare* CompletedSquare, bool bWillBeActivatingAgain = false) = 0;
	virtual void OnSquareFailed(GameSquare* FailedSquare) = 0 ;

protected:
	void Blink(bool bPermamentWhiteBlink);
};
