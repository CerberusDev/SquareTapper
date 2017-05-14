// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "GameScene.h"

USING_NS_CC;

const std::string LevelSelectScene::UnknownLevelImageFilePath_Idle = "LevelUnknown_idle.png";
const std::string LevelSelectScene::UnknownLevelImageFilePath_Pressed = "LevelUnknown_pressed.png";

bool LevelSelectScene::init()
{
	if (!Scene::init())
		return false;

	std::string FileName = "_Levels.txt";
	std::string FilePath = FileUtils::getInstance()->fullPathForFilename(FileName);
	std::string FileContents = FileUtils::getInstance()->getStringFromFile(FilePath);
	std::istringstream InputStream(FileContents);

	for (std::string Line; std::getline(InputStream, Line); )
	{
		if (Line.size() > 1 && Line[0] != '#')
		{
			LevelParams NewLevelParams;

			std::stringstream(Line) >> NewLevelParams.LevelNumber;
			std::getline(InputStream, Line);
			std::stringstream(Line) >> NewLevelParams.SquaresActivationTimeInterval;
			std::getline(InputStream, Line);
			std::stringstream(Line) >> NewLevelParams.TotalSquareActivationTime;
			std::getline(InputStream, Line);

			if (Line.find("Spawn mask") != std::string::npos)
			{
				NewLevelParams.bSpawnGameMask = true;
				std::getline(InputStream, Line);

				if (Line.find("Vertical") != std::string::npos)
					NewLevelParams.bVerticalMask = true;

				std::getline(InputStream, Line);

				if (Line.find("Killing") != std::string::npos)
					NewLevelParams.bKillingMask = true;
			}

			LevelParamsContainer.push_back(NewLevelParams);
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	auto label = Label::createWithTTF("Choose level", "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.9f));
	this->addChild(label, 1);

	Vector<MenuItem*> MenuItems;

	for (int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		std::stringstream StringStreamIdle;
		StringStreamIdle << "Level" << LevelParamsContainer[i].LevelNumber << "_idle.png";
		const bool bIdleImageExists = FileUtils::getInstance()->isFileExist(StringStreamIdle.str());
		const std::string IdleButtonFileName = bIdleImageExists ? StringStreamIdle.str() : UnknownLevelImageFilePath_Idle;

		std::stringstream StringStreamPressed;
		StringStreamPressed << "Level" << LevelParamsContainer[i].LevelNumber << "_pressed.png";
		const bool bPressedImageExists = FileUtils::getInstance()->isFileExist(StringStreamPressed.str());
		const std::string PressedButtonFileName = bPressedImageExists ? StringStreamPressed.str() : UnknownLevelImageFilePath_Pressed;

		auto LevelButton = MenuItemImage::create(IdleButtonFileName, PressedButtonFileName,
		[&](Ref* sender) {
			int LevelNumber = dynamic_cast<MenuItemImage*>(sender)->getTag();
			Director::getInstance()->replaceScene(GameScene::create(LevelParamsContainer[LevelNumber]));
		});
		LevelButton->setPosition(Vec2(visibleSize.width * 0.25f * (i % 3 + 1), visibleSize.height * (0.75 - 0.15f * (i / 3))));
		LevelButton->setTag(i);
		MenuItems.pushBack(LevelButton);
	}

	auto LevelMenu = Menu::createWithArray(MenuItems);
	LevelMenu->setPosition(Vec2::ZERO);
	this->addChild(LevelMenu, 1);

	return true;
}