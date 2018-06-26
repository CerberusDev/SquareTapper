// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"
#include "BaseScene.h"

class TutorialScene : public BaseScene
{
protected:
	static const std::string InstructionString_Standard;
	static const std::string InstructionString_DoubleTap;
	
	GameSquare* Square;
	ETutorialType TutorialType;
	int NextWorldNumber[(int)ETutorialType::MAX];

// ---------------------------------------------------------------------------------------------------

public:
	TutorialScene(ETutorialType argTutorialType);
	~TutorialScene();

	virtual bool init();

	static TutorialScene* create(ETutorialType argTutorialType);

	void InitTutorialStandard();
	void InitTutorialDoubleTap();
	virtual void OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain = false) override;
	virtual void OnSquareFailed(GameSquare* FailedSquare) override;
};
