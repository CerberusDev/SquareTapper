// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "TutorialScene.h"
#include "LevelSelectScene.h"
#include "GameSquareStandard.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool TutorialScene::init()
{
	if (!Scene::init())
		return false;

	VisibleSize = Director::getInstance()->getVisibleSize();

	const float InstructionLabelFontSize = 35.0f / Director::getInstance()->getContentScaleFactor();
	auto InstructionLabel = Label::createWithTTF("Tap the square when it starts playing animation", "fonts/ADAM.CGPRO.ttf", InstructionLabelFontSize);
	InstructionLabel->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.75f));
	InstructionLabel->setDimensions(VisibleSize.width * 0.68f, 0);
	this->addChild(InstructionLabel, 0);

	auto LevelButton = ui::Button::create("img/ui/ConfirmButton_idle.png", "img/ui/ConfirmButton_pressed.png");
	LevelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(GameScene::create(LevelSelectScene::GetLevelData()[0][0]));
	});
	LevelButton->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.2f));
	const float LevelButtonFontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	LevelButton->setTitleLabel(Label::createWithTTF("Got it!", "fonts/ADAM.CGPRO.ttf", LevelButtonFontSize));
	this->addChild(LevelButton, 0);

	auto SpawnSquare = CallFunc::create([&]() {
		Square = new GameSquareStandard(this, false, Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.5f), 0, 0);
		Square->SetBlockTouchEvents(true);
	});
	auto Delay1 = DelayTime::create(0.7f);
	auto ActivateSquare = CallFunc::create([&]() {
		Square->StartActivation(2.0f);
	});
	auto Delay2 = DelayTime::create(1.1f);
	auto TapSquare = CallFunc::create([&]() {
		Square->SimulateCorrectTap();

		const float TapLabelFontSize = 30.0f / Director::getInstance()->getContentScaleFactor();
		auto TapLabel = Label::createWithTTF("*Tap!*", "fonts/ADAM.CGPRO.ttf", TapLabelFontSize);
		TapLabel->setPosition(Vec2(VisibleSize.width * 0.58f, VisibleSize.height * 0.58f));
		this->addChild(TapLabel, 1);

		auto TestFunc = CallFunc::create([TapLabel]() {
			TapLabel->removeFromParent();
		});
		auto TestDelay = DelayTime::create(0.45f);

		TapLabel->runAction(Sequence::create(TestDelay, TestFunc, nullptr));
	});
	auto Delay3 = DelayTime::create(1.3f);
	auto DeleteSquare = CallFunc::create([&]() {
		delete Square;
	});

	runAction(RepeatForever::create(Sequence::create(SpawnSquare, Delay1, ActivateSquare, Delay2, TapSquare, Delay3, DeleteSquare, nullptr)));

	return true;
}

TutorialScene::~TutorialScene()
{
	delete Square;
}