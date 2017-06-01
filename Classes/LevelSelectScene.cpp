// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;

std::vector<std::vector<LevelParams> > LevelSelectScene::LevelParamsContainer;

LevelSelectScene::LevelSelectScene(int argStartWorldNumber) :
	StartWorldNumber(argStartWorldNumber)
{

}

LevelSelectScene* LevelSelectScene::create(int argStartWorldNumber)
{
	LevelSelectScene *pRet = new(std::nothrow) LevelSelectScene(argStartWorldNumber);

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

void LevelSelectScene::InitializeLevelParams()
{
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

				NewLevelParams.WorldNumber = LevelParamsContainer.size() - 1;
				std::stringstream(Line) >> NewLevelParams.LevelNumber;
				std::getline(InputStream, Line);
				std::stringstream(Line) >> NewLevelParams.SquaresActivationTimeInterval;
				std::getline(InputStream, Line);
				std::stringstream(Line) >> NewLevelParams.TotalSquareActivationTime;

				std::getline(InputStream, Line);
				std::stringstream DoubleTapSquaresSS(Line);
				int NextDoubleSquareIndex = 0;
				DoubleTapSquaresSS >> NextDoubleSquareIndex;

				while (NextDoubleSquareIndex != 0)
				{
					NewLevelParams.DoubleTapSquareIndices.push_back(NextDoubleSquareIndex);
					NextDoubleSquareIndex = 0;
					DoubleTapSquaresSS >> NextDoubleSquareIndex;
				}

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

	CCLOG("Level data initialization from file finished");
}

bool LevelSelectScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto PageViewMenu = ui::PageView::create();
	PageViewMenu->setContentSize(Size(visibleSize.width, visibleSize.height));
	PageViewMenu->setBounceEnabled(true);

	UserDefault* UserDefaultData = UserDefault::getInstance();

	for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		auto PageLayout = ui::Layout::create();
		PageLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
		PageViewMenu->addPage(PageLayout);

		for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
		{
			std::stringstream StringStreamLevelKey;
			StringStreamLevelKey << "Level" << LevelParamsContainer[i][j].LevelNumber;

			int StarsNumber = UserDefaultData->getIntegerForKey(StringStreamLevelKey.str().c_str(), 0);

			std::stringstream StringStreamIdle;
			StringStreamIdle << "img/ui/LevelButton" << StarsNumber << "_idle.png";

			std::stringstream StringStreamPressed;
			StringStreamPressed << "img/ui/LevelButton" << StarsNumber << "_pressed.png";

			auto LevelButton = ui::Button::create(StringStreamIdle.str(), StringStreamPressed.str());
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

			std::stringstream Stream;
			Stream << LevelParamsContainer[i][j].LevelNumber;
			float FontSize = 56.0f / Director::getInstance()->getContentScaleFactor();
			LevelButton->setTitleLabel(Label::createWithTTF(Stream.str(), "fonts/ADAM.CGPRO.ttf", FontSize));

			PageLayout->addChild(LevelButton);
		}
	}

	this->addChild(PageViewMenu, 0);
	PageViewMenu->setCurrentPageIndex(StartWorldNumber);

	auto ResetProgressButton = ui::Button::create("img/ui/ResetProgress_idle.png", "img/ui/ResetProgress_pressed.png");
	ResetProgressButton->setPosition(Vec2(visibleSize.width * 0.88f, visibleSize.height * 0.07));
	ResetProgressButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			UserDefault* UserDefaultData = UserDefault::getInstance();

			for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
			{
				for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
				{
					std::stringstream StringStreamLevelKey;
					StringStreamLevelKey << "Level" << LevelParamsContainer[i][j].LevelNumber;
					UserDefaultData->setIntegerForKey(StringStreamLevelKey.str().c_str(), 0);
				}
			}

			Director::getInstance()->replaceScene(LevelSelectScene::create(0));
		}

	});

	this->addChild(ResetProgressButton, 1);

	return true;
}