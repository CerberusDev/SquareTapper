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
	static const float InstructionLabelPosYMod = 41.0f;
	static const Vec2 TapLabelPosition = Vec2(417.0f, 908.0f);
	static const float TapLabelHideDelay = 0.5f;
	static const float Delay1 = 0.6f;
	static const float Delay2 = 0.9f;
	static const float Delay3 = 1.25f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, false, ESquareSafetyType::Standard, Vec2(GameScene::GetScreenPositionX(1), GameScene::GetScreenPositionY(3)), 0, 0);
		Square->SetBlockTouchEvents(true);
	});
	auto Delay1Action = DelayTime::create(Delay1);
	auto ActivateSquare = CallFunc::create([&]() {
		Square->StartActivation(SquareActivationTime);
	});
	auto Delay2Action = DelayTime::create(Delay2);
	auto TapSquare = CallFunc::create([&]() {
		Square->SimulateCorrectTap();

		const float TapLabelFontSize = 30.0f;
		auto TapLabel = Label::createWithTTF("*Tap!*", FONT_FILE_PATH_STANDARD, TapLabelFontSize);
		TapLabel->setPosition(TapLabelPosition);
		this->addChild(TapLabel, 1);

		auto HideTapLabel = CallFunc::create([TapLabel]() {
			TapLabel->removeFromParent();
		});
		auto TapDelay = DelayTime::create(TapLabelHideDelay);

		TapLabel->runAction(Sequence::create(TapDelay, HideTapLabel, nullptr));
	});
	auto Delay3Action = DelayTime::create(Delay3);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
		Square = nullptr;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1Action, ActivateSquare, Delay2Action, TapSquare, Delay3Action, DeleteSquare, nullptr)));

	CreateConfirationButton(DESIGN_RES_X / 2.0f, GameScene::GetScreenPositionY(0), WORLD_NUMBER_ON_TUTORIAL_STANDARD);
}

void TutorialScene::InitTutorialDoubleTap()
{
	static const float InstructionLabelPosYMod = 50.0f;
	static const Vec2 TapLabelPosition = Vec2(417.0f, 908.0f);
	static const Vec2 TapLabel2Position = Vec2(427.0f, 938.0f);
	static const float TapLabelHideDelay = 0.7f;
	static const float TapLabel2HideDelay = 0.48f;
	static const float Delay1 = 0.6f;
	static const float Delay2 = 0.9f;
	static const float Delay3 = 0.22f;
	static const float Delay4 = 1.4f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, true, ESquareSafetyType::Standard, Vec2(GameScene::GetScreenPositionX(1), GameScene::GetScreenPositionY(3)), 0, 0);
		Square->SetBlockTouchEvents(true);
	});
	auto Delay1Action = DelayTime::create(Delay1);
	auto ActivateSquare = CallFunc::create([&]() {
		Square->StartActivation(SquareActivationTime);
	});
	auto Delay2Action = DelayTime::create(Delay2);
	auto TapSquare = CallFunc::create([&]() {
		Square->SimulateCorrectTap();

		const float TapLabelFontSize = 30.0f;
		auto TapLabel = Label::createWithTTF("*Tap!*", FONT_FILE_PATH_STANDARD, TapLabelFontSize);
		TapLabel->setPosition(TapLabelPosition);
		this->addChild(TapLabel, 1);

		auto HideTapLabel = CallFunc::create([TapLabel]() {
			TapLabel->removeFromParent();
		});
		auto TapDelay = DelayTime::create(TapLabelHideDelay);

		TapLabel->runAction(Sequence::create(TapDelay, HideTapLabel, nullptr));
	});
	auto Delay3Action = DelayTime::create(Delay3);
	auto TapSquareSecondTime = CallFunc::create([&]() {
		Square->SimulateCorrectTap();

		const float TapLabelFontSize = 30.0f;
		auto TapLabel = Label::createWithTTF("*Tap!*", FONT_FILE_PATH_STANDARD, TapLabelFontSize);
		TapLabel->setPosition(TapLabel2Position);
		this->addChild(TapLabel, 1);

		auto HideTapLabel = CallFunc::create([TapLabel]() {
			TapLabel->removeFromParent();
		});
		auto TapDelay = DelayTime::create(TapLabel2HideDelay);

		TapLabel->runAction(Sequence::create(TapDelay, HideTapLabel, nullptr));
	});
	auto Delay4Action = DelayTime::create(Delay4);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
		Square = nullptr;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1Action, ActivateSquare, Delay2Action, TapSquare, Delay3Action, TapSquareSecondTime, Delay4Action, DeleteSquare, nullptr)));

	CreateConfirationButton(DESIGN_RES_X / 2.0f, GameScene::GetScreenPositionY(0), WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP);
}

void TutorialScene::CreateConfirationButton(float PosX, float PosY, int WorldNumberToTravelTo)
{
	auto LevelButton = ui::Button::create("gui/bqsqr/bgsqr_0_inactive_512.png", "gui/bqsqr/bgsqr_0_inactive_512.png");
	LevelButton->setScale(SQUARE_SPRITE_SIZE / SQUARE_TEXTURES_SIZE);
	LevelButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[WorldNumberToTravelTo][0]));
	});
	LevelButton->setPosition(Vec2(PosX, PosY));
	const float LevelButtonFontSize = 125.0f / Director::getInstance()->getContentScaleFactor();
	LevelButton->setTitleLabel(Label::createWithTTF("PLAY", FONT_FILE_PATH_STANDARD, LevelButtonFontSize));
	this->addChild(LevelButton, 0);
}
