// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "TutorialScene_Standard.h"
#include "LevelSelectScene.h"
#include "GameSquare.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool TutorialScene_Standard::init()
{
	if (!Scene::init())
		return false;

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

	return true;
}

TutorialScene_Standard::~TutorialScene_Standard()
{
	if (Square)
		delete Square;
}

void TutorialScene_Standard::OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain)
{
	Blink(true);

	auto DelayAction = DelayTime::create(0.9f);
	auto StartNextLevel = CallFunc::create([&]() {
		Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[WORLD_NUMBER_ON_TUTORIAL_STANDARD][0]));
	});
	runAction(Sequence::createWithTwoActions(DelayAction, StartNextLevel));
}

void TutorialScene_Standard::OnSquareFailed(GameSquare* FailedSquare)
{
	Blink(false);
}