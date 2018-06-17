// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#pragma once

#include "SquareTapper.h"

class GameSquare;

class TutorialScene : public cocos2d::Scene
{
protected:
	static const std::string InstructionString_Standard;
	static const std::string InstructionString_DoubleTap;
	
	GameSquare* Square;
	ETutorialType TutorialType;

// ---------------------------------------------------------------------------------------------------

public:
	TutorialScene(ETutorialType argTutorialType);
	~TutorialScene();

	virtual bool init();

	static TutorialScene* create(ETutorialType argTutorialType);

	void InitTutorialStandard();
	void InitTutorialDoubleTap();
	void CreateConfirationButton(float PosX, float PosY, int WorldNumberToTravelTo);
};
