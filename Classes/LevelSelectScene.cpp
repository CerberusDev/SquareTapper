// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "GameScene.h"
#include "TutorialScene.h"

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
	LevelParamsContainer.clear();

	int TotalLevelNumber = 0;
	std::string FilePath = FileUtils::getInstance()->fullPathForFilename("lvls/World_0.lvl");

	while (!FilePath.empty())
	{
		LevelParamsContainer.push_back(std::vector<LevelParams>());

		InitializeLevelParamsForSingleWorld(FilePath, TotalLevelNumber);

		std::stringstream FileNameStream;
		FileNameStream << "lvls/World_" << LevelParamsContainer.size() << ".lvl";
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
			ParamsStringStream >> NewLevelParams.SafeSquaresNumber;
			ParamsStringStream >> NewLevelParams.DangerousSquaresNumber;
			ParamsStringStream >> NewLevelParams.DangerousSecondTapSquaresNumber;

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

			NewLevelParams.DangerousSecondTapSquaresNumber = std::min(NewLevelParams.DangerousSecondTapSquaresNumber, (int)NewLevelParams.DoubleTapSquareIndices.size());

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

	while ((int)CurrLevelParamsStruct.SequencesSquareIndices.size() <= SequenceID)
		CurrLevelParamsStruct.SequencesSquareIndices.push_back(std::vector<int>());

	while ((int)CurrLevelParamsStruct.SequencesSquareIndices[SequenceID].size() <= SquareIndexInSequence)
		CurrLevelParamsStruct.SequencesSquareIndices[SequenceID].push_back(-1);
	
	CurrLevelParamsStruct.SequencesSquareIndices[SequenceID][SquareIndexInSequence] = SquareIndex;

	if (SquareType.find("DB") != std::string::npos)
		CurrLevelParamsStruct.SequenceDoubleTapSquareIndices.push_back(SquareIndex);
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

	for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		auto PageLayout = ui::Layout::create();
		PageLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
		PageViewMenu->addPage(PageLayout);

		for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
			CreateLevelButton(i, j, PageLayout);
	}

	this->addChild(PageViewMenu, 0);
	PageViewMenu->setCurrentPageIndex(StartWorldNumber);

	CreateResetProgressButton();

#ifdef _WINDOWS
	CreateReloadScriptsButton();
#endif

	return true;
}

void LevelSelectScene::CreateLevelButton(int WorldNumber, int LevelNumber, cocos2d::ui::Layout* PageLayout)
{
	static const float LevelButtonFontSize = 56.0f;

	std::string LevelKey = GetLevelRecordKey(LevelParamsContainer[WorldNumber][LevelNumber].LevelDisplayNumber);

	int StarsNumber = UserDefault::getInstance()->getIntegerForKey(LevelKey.c_str(), 0);

	std::stringstream StringStreamIdle;
	StringStreamIdle << "img/ui/LevelButton" << StarsNumber << "_idle.png";

	std::stringstream StringStreamPressed;
	StringStreamPressed << "img/ui/LevelButton" << StarsNumber << "_pressed.png";

	auto LevelButton = ui::Button::create(StringStreamIdle.str(), StringStreamPressed.str());
	LevelButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (LevelNumber == 0 && WorldNumber == WORLD_NUMBER_ON_TUTORIAL_STANDARD)
				Director::getInstance()->replaceScene(TutorialScene::create(ETutorialType::StandardSquare));
			else if (LevelNumber == 0 && WorldNumber == WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP)
				Director::getInstance()->replaceScene(TutorialScene::create(ETutorialType::DoubleTapSquare));
			else
				Director::getInstance()->replaceScene(GameScene::create(LevelParamsContainer[WorldNumber][LevelNumber]));
		}
	});
	LevelButton->setPosition(Vec2(180.0f * (LevelNumber % 3 + 1), 1280.0f * (0.8 - 0.15f * (LevelNumber / 3))));

	std::stringstream Stream;
	Stream << LevelParamsContainer[WorldNumber][LevelNumber].LevelDisplayNumber;
	LevelButton->setTitleLabel(Label::createWithTTF(Stream.str(), FONT_FILE_PATH_STANDARD, LevelButtonFontSize));

	PageLayout->addChild(LevelButton);
}

void LevelSelectScene::CreateResetProgressButton()
{
	auto ResetProgressButton = ui::Button::create("img/ui/ResetProgress_idle.png", "img/ui/ResetProgress_pressed.png");
	ResetProgressButton->setPosition(Vec2(634.0f, 90.0f));
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
}

void LevelSelectScene::CreateReloadScriptsButton()
{
	auto ReloadScriptsButton = ui::Button::create("gui/icons/icon_replay_inactive_512.png", "img/ui/icon_replay_active_512.png");
	ReloadScriptsButton->setPosition(Vec2(86.0f, 90.0f));
	ReloadScriptsButton->setScale(100.0f / 512.0f);
	ReloadScriptsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			LevelSelectScene::InitializeLevelParams();
			Director::getInstance()->replaceScene(LevelSelectScene::create(0));
		}
	});

	this->addChild(ReloadScriptsButton, 1);
}
