// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;

const std::string LevelSelectScene::UnknownLevelImageFilePath_Idle = "img/ui/level_buttons/LevelUnknown_idle.png";
const std::string LevelSelectScene::UnknownLevelImageFilePath_Pressed = "img/ui/level_buttons/LevelUnknown_pressed.png";

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
			if (Line[0] == '=')
			{
				LevelParamsContainer.push_back(std::vector<LevelParams>());
			}
			else
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

				LevelParamsContainer.back().push_back(NewLevelParams);
			}
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto PageViewMenu = ui::PageView::create();
	PageViewMenu->setContentSize(Size(visibleSize.width, visibleSize.height));
	PageViewMenu->setBounceEnabled(true);

	for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		auto PageLayout = ui::Layout::create();
		PageLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
		PageViewMenu->addPage(PageLayout);

		for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
		{
			std::stringstream StringStreamIdle;
			StringStreamIdle << "img/ui/level_buttons/Level" << LevelParamsContainer[i][j].LevelNumber << "_idle.png";
			const bool bIdleImageExists = FileUtils::getInstance()->isFileExist(StringStreamIdle.str());
			const std::string IdleButtonFileName = bIdleImageExists ? StringStreamIdle.str() : UnknownLevelImageFilePath_Idle;

			std::stringstream StringStreamPressed;
			StringStreamPressed << "img/ui/level_buttons/Level" << LevelParamsContainer[i][j].LevelNumber << "_pressed.png";
			const bool bPressedImageExists = FileUtils::getInstance()->isFileExist(StringStreamPressed.str());
			const std::string PressedButtonFileName = bPressedImageExists ? StringStreamPressed.str() : UnknownLevelImageFilePath_Pressed;;

			auto LevelButton = ui::Button::create(IdleButtonFileName, PressedButtonFileName, IdleButtonFileName);
			LevelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					const int LevelID = dynamic_cast<ui::Button*>(sender)->getTag();
					const int WorldNumber = LevelID / 1000;
					const int LevelNumber = LevelID - WorldNumber * 1000;

					Director::getInstance()->replaceScene(GameScene::create(LevelParamsContainer[WorldNumber][LevelNumber]));
				}
			});
			LevelButton->setPosition(Vec2(visibleSize.width * 0.25f * (j % 3 + 1), visibleSize.height * (0.75 - 0.15f * (j / 3))));
			LevelButton->setTag(1000 * i + j);

			PageLayout->addChild(LevelButton);
		}
	}

	this->addChild(PageViewMenu, 0);

	return true;
}