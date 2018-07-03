// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "BaseScene.h"

class TutorialScene_DoubleTap : public BaseScene
{
protected:
	GameSquare* Square;

// ---------------------------------------------------------------------------------------------------

public:
	CREATE_FUNC(TutorialScene_DoubleTap);

	~TutorialScene_DoubleTap();

	virtual bool init();

	virtual void OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain = false) override;
	virtual void OnSquareFailed(GameSquare* FailedSquare) override;
};
