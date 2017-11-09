// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "DebugScene.h"
#include "LevelSelectScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool DebugScene::init()
{
	if (!Scene::init())
		return false;

	auto BackButton = ui::Button::create("gui/icons/icon_menu_inactive_512.png", "img/ui/icon_menu_inactive_512.png");
	BackButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(LevelSelectScene::create(0));
		}
	});

	BackButton->setPosition(Vec2(GameScene::GetScreenPositionX(0), GameScene::GetButtonsPositionY()));
	BackButton->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	this->addChild(BackButton, 1);

	UserDefault* UserDefaultData = UserDefault::getInstance();

	for (int i = 14; i >= 0; --i)
	{
		std::string LevelKey = GetLevelRecordKey(LevelSelectScene::GetLevelData()[0][i].GetLevelID());

		for (int j = 1; j <= 3; ++j)
		{
			if (i == 0)
			{
				std::stringstream Stream0;
				Stream0 << j << (j == 1 ? " star" : " stars");
				auto StarLabel = Label::createWithTTF(Stream0.str(), FONT_FILE_PATH_STANDARD, 30.0f);
				StarLabel->setPosition(Vec2(140.0f + 150.0f * j, 1200.0f));
				StarLabel->setColor(GOLD_COLOR);
				this->addChild(StarLabel, 1);
			}

			std::stringstream Stream;
			Stream << "DEMO" << LevelKey << j;
			int AttemptsNumber = UserDefaultData->getIntegerForKey(Stream.str().c_str(), 0);

			std::stringstream Stream2;
			Stream2 << AttemptsNumber;
			auto AttemptsLabel = Label::createWithTTF(Stream2.str(), FONT_FILE_PATH_STANDARD, 40.0f);
			AttemptsLabel->setPosition(Vec2(140.0f + 150.0f * j, 150.0f + 70.0f * i));
			AttemptsLabel->setColor(GREY_COLOR);
			this->addChild(AttemptsLabel, 1);

			std::stringstream Stream3;
			Stream3 << "lvl " << LevelSelectScene::GetLevelData()[0][i].LevelDisplayNumber;
			auto LevelLabel = Label::createWithTTF(Stream3.str(), FONT_FILE_PATH_STANDARD, 30.0f);
			LevelLabel->setPosition(Vec2(120.0f, 150.0f + 70.0f * i));
			LevelLabel->setColor(GREY_COLOR);
			this->addChild(LevelLabel, 1);
		}
	}



	return true;
}
