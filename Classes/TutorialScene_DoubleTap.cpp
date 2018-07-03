// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "TutorialScene_DoubleTap.h"
#include "LevelSelectScene.h"
#include "GameSquare.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool TutorialScene_DoubleTap::init()
{
	if (!Scene::init())
		return false;

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

	return true;
}

TutorialScene_DoubleTap::~TutorialScene_DoubleTap()
{
	if (Square)
		delete Square;
}

void TutorialScene_DoubleTap::OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain)
{
	Blink(true);

	auto DelayAction = DelayTime::create(0.9f);
	auto StartNextLevel = CallFunc::create([&]() {
		Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP][0]));
	});
	runAction(Sequence::createWithTwoActions(DelayAction, StartNextLevel));
}

void TutorialScene_DoubleTap::OnSquareFailed(GameSquare* FailedSquare)
{
	Blink(false);
}