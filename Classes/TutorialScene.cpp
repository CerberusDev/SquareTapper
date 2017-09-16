// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "TutorialScene.h"
#include "LevelSelectScene.h"
#include "GameSquare.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#define INSTRUCTION_LABEL_POS_Y 960.0f
#define INSTRUCTION_LABEL_WIDTH 500.0f
#define BUTTON_POS_Y 250.0f
#define SQUARE_POS_Y 640.0f

const std::string TutorialScene::InstructionString_Standard = "Tap the square when white square appears";
const std::string TutorialScene::InstructionString_DoubleTap = "This kind of square requires two taps";

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
	static const Vec2 TapLabelPosition = Vec2(417.0f, 742.0f);
	static const float TapLabelHideDelay = 0.5f;
	static const float Delay1 = 0.7f;
	static const float Delay2 = 1.1f;
	static const float Delay3 = 1.35f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, false, ESquareSafetyType::Standard, Vec2(DESIGN_RES_X / 2.0f, SQUARE_POS_Y), 0, 0);
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

	CreateInstructionLabel(InstructionString_Standard, DESIGN_RES_X / 2.0f + InstructionLabelPosYMod, INSTRUCTION_LABEL_POS_Y);
	CreateConfirationButton(DESIGN_RES_X / 2.0f, BUTTON_POS_Y, WORLD_NUMBER_ON_TUTORIAL_STANDARD);
}

void TutorialScene::InitTutorialDoubleTap()
{
	static const float InstructionLabelPosYMod = 50.0f;
	static const Vec2 TapLabelPosition = Vec2(417.0f, 742.0f);
	static const Vec2 TapLabel2Position = Vec2(427.0f, 772.0f);
	static const float TapLabelHideDelay = 0.65f;
	static const float TapLabel2HideDelay = 0.43f;
	static const float Delay1 = 0.7f;
	static const float Delay2 = 1.1f;
	static const float Delay3 = 0.22f;
	static const float Delay4 = 1.5f;
	static const float SquareActivationTime = 2.0f;

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquare(this, true, ESquareSafetyType::Standard, Vec2(DESIGN_RES_X / 2.0f, SQUARE_POS_Y), 0, 0);
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
		auto TapDelay = DelayTime::create(0.43f);

		TapLabel->runAction(Sequence::create(TapDelay, HideTapLabel, nullptr));
	});
	auto Delay4Action = DelayTime::create(Delay4);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
		Square = nullptr;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1Action, ActivateSquare, Delay2Action, TapSquare, Delay3Action, TapSquareSecondTime, Delay4Action, DeleteSquare, nullptr)));

	CreateInstructionLabel(InstructionString_DoubleTap, DESIGN_RES_X / 2.0f + InstructionLabelPosYMod, INSTRUCTION_LABEL_POS_Y);
	CreateConfirationButton(DESIGN_RES_X / 2.0f, BUTTON_POS_Y, WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP);
}

void TutorialScene::CreateInstructionLabel(const std::string& InstructionString, float PosX, float PosY)
{
	const float InstructionLabelFontSize = 35.0f;
	auto InstructionLabel = Label::createWithTTF(InstructionString, FONT_FILE_PATH_STANDARD, InstructionLabelFontSize);
	InstructionLabel->setPosition(Vec2(PosX, PosY));
	InstructionLabel->setDimensions(INSTRUCTION_LABEL_WIDTH, 0);
	this->addChild(InstructionLabel, 0);
}

void TutorialScene::CreateConfirationButton(float PosX, float PosY, int WorldNumberToTravelTo)
{
	auto LevelButton = ui::Button::create("img/ui/ConfirmButton_idle.png", "img/ui/ConfirmButton_pressed.png");
	LevelButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[WorldNumberToTravelTo][0]));
	});
	LevelButton->setPosition(Vec2(PosX, PosY));
	const float LevelButtonFontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	LevelButton->setTitleLabel(Label::createWithTTF("Got it!", FONT_FILE_PATH_STANDARD, LevelButtonFontSize));
	this->addChild(LevelButton, 0);
}
