// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "BaseScene.h"

class TutorialScene_Standard : public BaseScene
{
protected:
	GameSquare* Square;

// ---------------------------------------------------------------------------------------------------

public:
	CREATE_FUNC(TutorialScene_Standard);

	~TutorialScene_Standard();

	virtual bool init();

	virtual void OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain = false) override;
	virtual void OnSquareFailed(GameSquare* FailedSquare) override;
};
