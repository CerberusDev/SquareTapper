// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "TutorialScene.h"
#include "LevelSelectScene.h"
#include "GameSquare.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

TutorialScene::TutorialScene(ETutorialType argTutorialType) :
TutorialType(argTutorialType)
{
	NextWorldNumber[(int)ETutorialType::StandardSquare] = WORLD_NUMBER_ON_TUTORIAL_STANDARD;
	NextWorldNumber[(int)ETutorialType::DoubleTapSquare] = WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP;
}

TutorialScene* TutorialScene::create(ETutorialType argTutorialType)
{
	TutorialScene *pRet = new(std::nothrow) TutorialScene(argTutorialType);

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool TutorialScene::init()
{
	if (!Scene::init())
		return false;

	switch (TutorialType)
	{
	case ETutorialType::StandardSquare:		InitTutorialStandard();		break;
	case ETutorialType::DoubleTapSquare:	InitTutorialDoubleTap();	break;
	}

	return true;
}

TutorialScene::~TutorialScene()
{
	if (Square)
		delete Square;
}

void TutorialScene::InitTutorialStandard()
{
	static const float Delay1 = 0.6f;
	static const float Delay2 = 3.0f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, false, ESquareSafetyType::Standard, Vec2(GameScene::GetScreenPositionX(1), GameScene::GetScreenPositionY(3)), 0, 0);
	});
	auto Delay1Action = DelayTime::create(Delay1);
	auto ActivateSquare = CallFunc::create([&]() {
		Square->StartActivation(SquareActivationTime);
	});
	auto Delay2Action = DelayTime::create(Delay2);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
		Square = nullptr;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1Action, ActivateSquare, Delay2Action, DeleteSquare, nullptr)));
}

void TutorialScene::InitTutorialDoubleTap()
{
	static const float Delay1 = 0.6f;
	static const float Delay2 = 3.15f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, true, ESquareSafetyType::Standard, Vec2(GameScene::GetScreenPositionX(1), GameScene::GetScreenPositionY(3)), 0, 0);

	});
	auto Delay1Action = DelayTime::create(Delay1);
	auto ActivateSquare = CallFunc::create([&]() {
		Square->StartActivation(SquareActivationTime);
	});
	auto Delay2Action = DelayTime::create(Delay2);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
		Square = nullptr;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1Action, ActivateSquare, Delay2Action, DeleteSquare, nullptr)));
}

void TutorialScene::OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain)
{
	switch (TutorialType)
	{
	case ETutorialType::StandardSquare:
	{
		Blink(true);

		auto DelayAction = DelayTime::create(0.9f);
		auto StartNextLevel = CallFunc::create([&]() {
			Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[NextWorldNumber[(int)TutorialType]][0]));
		});
		runAction(Sequence::createWithTwoActions(DelayAction, StartNextLevel));
		break;

	}
	case ETutorialType::DoubleTapSquare:	
	{
		Blink(true);

		auto DelayAction = DelayTime::create(0.9f);
		auto StartNextLevel = CallFunc::create([&]() {
			Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[NextWorldNumber[(int)TutorialType]][0]));
		});
		runAction(Sequence::createWithTwoActions(DelayAction, StartNextLevel));
		break;
	}
	}
}

void TutorialScene::OnSquareFailed(GameSquare* FailedSquare)
{
	Blink(false);
}