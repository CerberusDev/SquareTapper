// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "GameScene.h"
#include "TutorialScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

std::vector<std::vector<LevelParams>> LevelSelectScene::LevelParamsContainer;

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
	int TotalLevelNumber = 0;
	std::string FilePath = FileUtils::getInstance()->fullPathForFilename("World_0.lvl");

	while (!FilePath.empty())
	{
		LevelParamsContainer.push_back(std::vector<LevelParams>());

		InitializeLevelParamsForSingleWorld(FilePath, TotalLevelNumber);

		std::stringstream FileNameStream;
		FileNameStream << "World_" << LevelParamsContainer.size() << ".lvl";
		FilePath = FileUtils::getInstance()->fullPathForFilename(FileNameStream.str());
	}

	CCLOG("Level data initialization from file finished");
}

void LevelSelectScene::InitializeLevelParamsForSingleWorld(const std::string& FilePath, int& TotalLevelNumber)
{
	std::string FileContents = FileUtils::getInstance()->getStringFromFile(FilePath);
	std::istringstream InputStream(FileContents);

	for (std::string Line; std::getline(InputStream, Line); )
	{
		if (Line.size() > 1 && Line[0] != '#')
		{
			LevelParams NewLevelParams;

			NewLevelParams.WorldNumber = LevelParamsContainer.size() - 1;
			NewLevelParams.LevelNumber = LevelParamsContainer.back().size();
			NewLevelParams.LevelDisplayNumber = ++TotalLevelNumber;

			std::stringstream ParamsStringStream(Line);

			ParamsStringStream >> NewLevelParams.SquaresActivationTimeInterval;
			ParamsStringStream >> NewLevelParams.TotalSquareActivationTime;
			ParamsStringStream >> NewLevelParams.DangerousSquaresNumber;

			if (Line.find("SpawnMask") != std::string::npos)
			{
				NewLevelParams.bSpawnGameMask = true;

				if (Line.find("Vertical") != std::string::npos)
					NewLevelParams.bVerticalMask = true;

				if (Line.find("Killing") != std::string::npos)
					NewLevelParams.bKillingMask = true;
			}

			std::getline(InputStream, Line);

			for (int i = SQUARE_AMOUNT_Y - 1; i >= 0; --i)
			{
				std::getline(InputStream, Line);
				std::stringstream SquaresStringStream(Line);

				for (int j = 1; j <= SQUARE_AMOUNT_X; ++j)
				{
					int SquareIndex = i * SQUARE_AMOUNT_X + j;
					std::string SquareType;
					SquaresStringStream >> SquareType;

					if (SquareType == "DB")
						NewLevelParams.DoubleTapSquareIndices.push_back(SquareIndex);
					else if (SquareType.find("SQ") != std::string::npos)
						AddSequenceSquareToLevelParams(NewLevelParams, SquareType, SquareIndex);
				}
			}

			LevelParamsContainer.back().push_back(NewLevelParams);
		}
	}
}

void LevelSelectScene::AddSequenceSquareToLevelParams(LevelParams& CurrLevelParamsStruct, const std::string& SquareType, int SquareIndex)
{
	std::string Tail = SquareType.substr(SquareType.size() - 3);
	std::replace(Tail.begin(), Tail.end(), '.', ' ');
	std::stringstream TailStringStream(Tail);

	int SequenceID, SquareIndexInSequence;
	
	TailStringStream >> SequenceID;
	TailStringStream >> SquareIndexInSequence;

	while (CurrLevelParamsStruct.SequencesSquareIndices.size() <= SequenceID)
		CurrLevelParamsStruct.SequencesSquareIndices.push_back(std::vector<int>());

	while (CurrLevelParamsStruct.SequencesSquareIndices[SequenceID].size() <= SquareIndexInSequence)
		CurrLevelParamsStruct.SequencesSquareIndices[SequenceID].push_back(-1);
	
	CurrLevelParamsStruct.SequencesSquareIndices[SequenceID][SquareIndexInSequence] = SquareIndex;
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
	const float LevelButtonFontSize = 56.0f / Director::getInstance()->getContentScaleFactor();

	for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		auto PageLayout = ui::Layout::create();
		PageLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
		PageViewMenu->addPage(PageLayout);

		for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
		{
			std::string LevelKey = GetLevelRecordKey(LevelParamsContainer[i][j].LevelDisplayNumber);

			int StarsNumber = UserDefaultData->getIntegerForKey(LevelKey.c_str(), 0);

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

					if (WorldNumber == 0 && LevelNumber == 0)
						Director::getInstance()->replaceScene(TutorialScene::create());
					else
						Director::getInstance()->replaceScene(GameScene::create(LevelParamsContainer[WorldNumber][LevelNumber]));
				}
			});
			LevelButton->setPosition(Vec2(visibleSize.width * 0.25f * (j % 3 + 1), visibleSize.height * (0.75 - 0.15f * (j / 3))));
			LevelButton->setTag(1000 * i + j);

			std::stringstream Stream;
			Stream << LevelParamsContainer[i][j].LevelDisplayNumber;
			LevelButton->setTitleLabel(Label::createWithTTF(Stream.str(), "fonts/ADAM.CGPRO.ttf", LevelButtonFontSize));

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
					const std::string LevelRecordKey = GetLevelRecordKey(LevelParamsContainer[i][j].LevelDisplayNumber);
					UserDefaultData->setIntegerForKey(LevelRecordKey.c_str(), 0);
					const std::string LevelAttemptsKey = GetLevelAttemptsKey(LevelParamsContainer[i][j].LevelDisplayNumber);
					UserDefaultData->setIntegerForKey(LevelAttemptsKey.c_str(), 0);
				}
			}

			Director::getInstance()->replaceScene(LevelSelectScene::create(0));
		}

	});

	this->addChild(ResetProgressButton, 1);

	return true;
}