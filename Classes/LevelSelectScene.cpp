// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "GameScene.h"
#include "TutorialScene.h"

USING_NS_CC;

#define ARROW_ICON_SIZE 120.0f

const std::string LevelSelectScene::LevelButtonSpriteFilename_0Stars = "gui/squares/square_active_512.png";
const std::string LevelSelectScene::LevelButtonSpriteFilename_1Star = "gui/percent/percent_33_inactive_star_512.png";
const std::string LevelSelectScene::LevelButtonSpriteFilename_2Stars = "gui/percent/percent_66_inactive_star_512.png";
const std::string LevelSelectScene::LevelButtonSpriteFilename_3Stars = "gui/percent/percent_100_inactive_star_512.png";
const std::string LevelSelectScene::LevelButtonSpriteFilename_Locked = "gui/bqsqr/bgsqr_0_inactive_512.png";
const std::string LevelSelectScene::LevelButtonSpriteFilename_Locked_Bonus = "gui/bqsqr/bgsqr_9_inactive_512.png";

const std::string LevelSelectScene::UDDKeyLastSeenWorld = "LastSeenWorld";

std::vector<std::vector<LevelParams>> LevelSelectScene::LevelParamsContainer;
std::vector<int> LevelSelectScene::RequiredStarsPerWorld;
std::vector<std::string> LevelSelectScene::IconNamePerWorld;

LevelSelectScene::LevelSelectScene() :
TotalNumberOfStars(0)
{
	UserDefault* UserDefaultData = UserDefault::getInstance();
	StartWorldNumber = UserDefaultData->getIntegerForKey(UDDKeyLastSeenWorld.c_str(), 0);
}

LevelSelectScene* LevelSelectScene::create()
{
	LevelSelectScene *pRet = new(std::nothrow) LevelSelectScene();

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
	InitializeIconsAndRequiredStars();

	LevelParamsContainer.clear();

	std::string FilePath = FileUtils::getInstance()->fullPathForFilename(GenerateFilenameForWorldConfig(0));

	while (!FilePath.empty())
	{
		LevelParamsContainer.push_back(std::vector<LevelParams>());

		InitializeLevelParamsForSingleWorld(FilePath);

		int NextWorldNumber = LevelParamsContainer.size();
		FilePath = FileUtils::getInstance()->fullPathForFilename(GenerateFilenameForWorldConfig(NextWorldNumber));
	}

	CCLOG("Level data initialization from file finished");
}

void LevelSelectScene::InitializeIconsAndRequiredStars()
{
	RequiredStarsPerWorld.clear();
	IconNamePerWorld.clear();

	std::string FileContents = FileUtils::getInstance()->getStringFromFile("lvls/_Info.txt");
	std::istringstream InputStream(FileContents);

	bool bReadingIconNames = true;

	for (std::string Line; std::getline(InputStream, Line); )
	{
		if (Line.size() < 2)
		{
			bReadingIconNames = false;
		}
		else
		{
			if (bReadingIconNames)
			{
				std::string IconFilename;
				std::stringstream IconFilenameStringStream(Line);
				IconFilenameStringStream >> IconFilename;
				IconNamePerWorld.push_back("gui/signs/" + IconFilename);
			}
			else
			{
				int RequiredStars;
				std::stringstream RequiredStarsStringStream(Line);
				RequiredStarsStringStream >> RequiredStars;
				RequiredStarsPerWorld.push_back(RequiredStars);
			}
		}
	}
}

std::string LevelSelectScene::GenerateFilenameForWorldConfig(int WorldNumber)
{
	std::stringstream Stream;
	std::string LevelsDirectoryName = "lvls";

	Stream << LevelsDirectoryName << "/World_" << WorldNumber << ".lvl";
	return Stream.str();
}

void LevelSelectScene::InitializeLevelParamsForSingleWorld(const std::string& FilePath)
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

			if (NewLevelParams.LevelNumber < STANDARD_LEVELS_PER_WORLD)
			{
				std::stringstream Stream;
				Stream << NewLevelParams.WorldNumber * STANDARD_LEVELS_PER_WORLD + NewLevelParams.LevelNumber + 1;
				NewLevelParams.LevelDisplayNumber = Stream.str();
			}
			else
			{
				switch (NewLevelParams.LevelNumber)
				{
				case 12:	NewLevelParams.LevelDisplayNumber = "I";	break;
				case 13:	NewLevelParams.LevelDisplayNumber = "II";	break;
				case 14:	NewLevelParams.LevelDisplayNumber = "III";	break;
				}
			}

			std::stringstream ParamsStringStream(Line);

			ParamsStringStream >> NewLevelParams.SquaresActivationTimeInterval;
			ParamsStringStream >> NewLevelParams.TotalSquareActivationTime;
			ParamsStringStream >> NewLevelParams.SafeSquaresNumber;
			ParamsStringStream >> NewLevelParams.DangerousSquaresNumber;
			ParamsStringStream >> NewLevelParams.DangerousSecondTapSquaresNumber;

			if (Line.find("Vertical-Killing") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Vertical, true));
			else if (Line.find("Vertical-Standard") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Vertical, false));

			if (Line.find("Horizontal-Killing") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Horizontal, true));
			else if (Line.find("Horizontal-Standard") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Horizontal, false));

			if (Line.find("HorizontalBig-Killing") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::HorizontalBig, true));
			else if (Line.find("HorizontalBig-Standard") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::HorizontalBig, false));

			if (Line.find("Chessboard-Killing") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Chessboard, true));
			else if (Line.find("Chessboard-Standard") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Chessboard, false));

			if (Line.find("Full-Killing") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Full, true));
			else if (Line.find("Full-Standard") != std::string::npos)
				NewLevelParams.Masks.push_back(MaskDefiniton(EMaskType::Full, false));

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
	int TailStartPos = SquareType.find('.') + 1;
	std::string Tail = SquareType.substr(TailStartPos, SquareType.length() - TailStartPos);
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

	std::vector<ui::Layout*> PageLayouts;

	for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
	{
		auto PageLayout = ui::Layout::create();
		PageLayouts.push_back(PageLayout);
		PageLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
		PageViewMenu->addPage(PageLayout);

		const bool bWorldLocked = (TotalNumberOfStars < RequiredStarsPerWorld[i]);
		bool bMaxStarsOnStandardLevels = true;
		int StarsOnLastStandardLevel = -1;

		for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
		{
			std::string LevelKey = GetLevelRecordKey(LevelParamsContainer[i][j].GetLevelID());
			int StarsNumber = UserDefault::getInstance()->getIntegerForKey(LevelKey.c_str(), 0);
			TotalNumberOfStars += StarsNumber;

			if (bWorldLocked)
			{
				LevelParamsContainer[i][j].bLocked = true;
			}
			else
			{
				if (j < STANDARD_LEVELS_PER_WORLD)
				{
					if (StarsNumber != 3)
						bMaxStarsOnStandardLevels = false;

					LevelParamsContainer[i][j].bLocked = (StarsOnLastStandardLevel == 0);
					StarsOnLastStandardLevel = StarsNumber;
				}
				else
				{
					LevelParamsContainer[i][j].bLocked = !bMaxStarsOnStandardLevels;
				}
			}

			CreateLevelButton(i, j, StarsNumber, PageLayout);
		}

		if (bWorldLocked)
			CreateRequiredStarsLabel(i, PageLayout);
		else
			CreateWorldIcon(i, PageLayout);

		CreateTopArrowsIcons(i, PageLayout);

		std::stringstream DebugWorldStream;
		DebugWorldStream << "World_" << i;
		auto DebugWorldLabel = Label::createWithTTF(DebugWorldStream.str(), FONT_FILE_PATH_STANDARD, 22.0f);
		DebugWorldLabel->setPosition(Vec2(80.0f, 1235.0f));
		DebugWorldLabel->setColor(Color3B::RED);
		PageLayout->addChild(DebugWorldLabel, 1);
	}

	for (ui::Layout* PageLayout : PageLayouts)
		CreateStarsLabel(PageLayout);

	this->addChild(PageViewMenu, 0);
	PageViewMenu->setCurrentPageIndex(StartWorldNumber);

	CreateResetProgressButton();
	CreateBackToMenuButton();
	CreateDebugButton();

	return true;
}

void LevelSelectScene::CreateLevelButton(int WorldNumber, int LevelNumber, int StarsNumber, cocos2d::ui::Layout* PageLayout)
{
	static const float LevelButtonFontSize = 180.0f;

	auto LevelButton = ui::Button::create();
	LevelButton->setScale(SQUARE_SPRITE_SIZE / SQUARE_TEXTURES_SIZE);
	Vec2 LevelButtonPostion;
	LevelButtonPostion.x = GameScene::GetScreenPositionX(LevelNumber % SQUARE_AMOUNT_X);
	LevelButtonPostion.y = GameScene::GetScreenPositionY((SQUARE_AMOUNT_X * SQUARE_AMOUNT_Y - 1 - LevelNumber) / SQUARE_AMOUNT_X);
	LevelButton->setPosition(LevelButtonPostion);

	if (LevelParamsContainer[WorldNumber][LevelNumber].bLocked)
	{
		if (LevelNumber < STANDARD_LEVELS_PER_WORLD)
			LevelButton->loadTextures(LevelButtonSpriteFilename_Locked, LevelButtonSpriteFilename_Locked);
		else
			LevelButton->loadTextures(LevelButtonSpriteFilename_Locked_Bonus, LevelButtonSpriteFilename_Locked_Bonus);
	}
	else
	{
		LevelButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				UserDefault* UserDefaultData = UserDefault::getInstance();
				UserDefaultData->setIntegerForKey(UDDKeyLastSeenWorld.c_str(), WorldNumber);
				UserDefaultData->flush();

				if (LevelNumber == 0 && WorldNumber == WORLD_NUMBER_ON_TUTORIAL_STANDARD)
					Director::getInstance()->replaceScene(TutorialScene::create(ETutorialType::StandardSquare));
				else if (LevelNumber == 0 && WorldNumber == WORLD_NUMBER_ON_TUTORIAL_DOUBLE_TAP)
					Director::getInstance()->replaceScene(TutorialScene::create(ETutorialType::DoubleTapSquare));
				else
					Director::getInstance()->replaceScene(GameScene::create(LevelParamsContainer[WorldNumber][LevelNumber]));
			}
		});

		std::stringstream Stream;
		Stream << LevelParamsContainer[WorldNumber][LevelNumber].LevelDisplayNumber;
		LevelButton->setTitleLabel(Label::createWithTTF(Stream.str(), FONT_FILE_PATH_STANDARD, LevelButtonFontSize, Size(0.0f, 290.0f)));
		LevelButton->setTitleColor(BACKGROUND_COLOR);

		const std::string& LevelButtonSpriteFilename = GetLevelButtonSpriteFilename(StarsNumber);
		LevelButton->loadTextures(LevelButtonSpriteFilename, LevelButtonSpriteFilename);
	}

	PageLayout->addChild(LevelButton);
}

const std::string& LevelSelectScene::GetLevelButtonSpriteFilename(int StarsNumber)
{
	switch (StarsNumber)
	{
	case 3:		return LevelButtonSpriteFilename_3Stars;
	case 2:		return LevelButtonSpriteFilename_2Stars;
	case 1:		return LevelButtonSpriteFilename_1Star;
										
	default:	return LevelButtonSpriteFilename_0Stars;
	}
}

void LevelSelectScene::CreateWorldIcon(int WorldNumber, cocos2d::ui::Layout* PageLayout)
{
	auto WorldIcon = Sprite::create(IconNamePerWorld[WorldNumber]);
	WorldIcon->setPosition(Vec2(DESIGN_RES_X / 2.0f, GameScene::GetScreenPositionY(SQUARE_AMOUNT_Y)));
	WorldIcon->setScale(SQUARE_SPRITE_SIZE / SQUARE_TEXTURES_SIZE);
	PageLayout->addChild(WorldIcon);
}

void LevelSelectScene::CreateTopArrowsIcons(int WorldNumber, cocos2d::ui::Layout* PageLayout)
{
	auto LeftArrowIcon = Sprite::create();

	if (WorldNumber == 0)
		LeftArrowIcon->setTexture("gui/icons/icon_left_inactive_512.png");
	else
		LeftArrowIcon->setTexture("gui/icons/icon_right_active_512.png");

	LeftArrowIcon->setFlippedX(true);
	LeftArrowIcon->setScale(ARROW_ICON_SIZE / BUTTON_TEXTURES_SIZE);
	LeftArrowIcon->setPosition(Vec2(GameScene::GetScreenPositionX(0), GameScene::GetStarPositionY()));
	PageLayout->addChild(LeftArrowIcon);

	auto RightArrowIcon = Sprite::create();

	if (WorldNumber == LevelParamsContainer.size() - 1)
		RightArrowIcon->setTexture("gui/icons/icon_left_inactive_512.png");
	else
		RightArrowIcon->setTexture("gui/icons/icon_right_active_512.png");

	RightArrowIcon->setScale(ARROW_ICON_SIZE / BUTTON_TEXTURES_SIZE);
	RightArrowIcon->setPosition(Vec2(GameScene::GetScreenPositionX(MAX_STARS_NUMBER - 1), GameScene::GetStarPositionY()));
	PageLayout->addChild(RightArrowIcon);
}

void LevelSelectScene::CreateRequiredStarsLabel(int WorldNumber, cocos2d::ui::Layout* PageLayout)
{
	float LabelFontSize = 40.0f;
	std::stringstream Stream;
	Stream << "." << RequiredStarsPerWorld[WorldNumber];
	auto StarsLabel = Label::createWithTTF(Stream.str(), FONT_FILE_PATH_STANDARD, LabelFontSize);
	StarsLabel->setPosition(Vec2(GameScene::GetScreenPositionX(0), GameScene::GetLabelsPositionY()));
	StarsLabel->setColor(GOLD_COLOR);
	PageLayout->addChild(StarsLabel);
}

void LevelSelectScene::CreateStarsLabel(cocos2d::ui::Layout* PageLayout)
{
	float LabelFontSize = 40.0f;
	std::stringstream Stream;
	Stream << "." << TotalNumberOfStars;
	auto StarsLabel = Label::createWithTTF(Stream.str(), FONT_FILE_PATH_STANDARD, LabelFontSize);
	StarsLabel->setPosition(Vec2(GameScene::GetScreenPositionX(MAX_STARS_NUMBER - 1), GameScene::GetLabelsPositionY()));
	StarsLabel->setColor(GOLD_COLOR);
	PageLayout->addChild(StarsLabel);
}

void LevelSelectScene::CreateResetProgressButton()
{
	auto ResetProgressButton = ui::Button::create("img/ui/ResetProgress_new.png", "img/ui/ResetProgress_new.png");
	ResetProgressButton->setScale(0.3f);
	ResetProgressButton->setPosition(Vec2(GameScene::GetScreenPositionX(2), GameScene::GetButtonsPositionY()));
	ResetProgressButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			UserDefault* UserDefaultData = UserDefault::getInstance();

			for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
			{
				for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
				{
					const std::string LevelRecordKey = GetLevelRecordKey(LevelParamsContainer[i][j].GetLevelID());
					UserDefaultData->setIntegerForKey(LevelRecordKey.c_str(), 0);
					const std::string LevelAttemptsKey = GetLevelAttemptsKey(LevelParamsContainer[i][j].GetLevelID());
					UserDefaultData->setIntegerForKey(LevelAttemptsKey.c_str(), 0);
				}
			}

			UserDefaultData->setIntegerForKey(UDDKeyLastSeenWorld.c_str(), 0);
			UserDefaultData->flush();

			Director::getInstance()->replaceScene(LevelSelectScene::create());
		}
	});

	this->addChild(ResetProgressButton, 1);
}

void LevelSelectScene::CreateDebugButton()
{
	auto DebugButton = ui::Button::create("img/ui/DebugButton.png", "img/ui/DebugButton.png");
	DebugButton->setPosition(Vec2(GameScene::GetScreenPositionX(1), GameScene::GetButtonsPositionY()));
	DebugButton->setScale(100.0f / 512.0f);
	DebugButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			UserDefault* UserDefaultData = UserDefault::getInstance();

			for (unsigned int i = 0; i < LevelParamsContainer.size(); ++i)
			{
				for (unsigned int j = 0; j < LevelParamsContainer[i].size(); ++j)
				{
					const std::string LevelRecordKey = GetLevelRecordKey(LevelParamsContainer[i][j].GetLevelID());
					UserDefaultData->setIntegerForKey(LevelRecordKey.c_str(), 3);
				}
			}

			UserDefaultData->flush();

			LevelSelectScene::InitializeLevelParams();
			Director::getInstance()->replaceScene(LevelSelectScene::create());
		}
	});

	this->addChild(DebugButton, 1);
}

void LevelSelectScene::CreateBackToMenuButton()
{
	auto BackToMenuButton = ui::Button::create("gui/icons/icon_menu_inactive_512.png", "img/ui/icon_menu_inactive_512.png");
	BackToMenuButton->setPosition(Vec2(GameScene::GetScreenPositionX(0), GameScene::GetButtonsPositionY()));
	BackToMenuButton->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);

	BackToMenuButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//temporary: do nothing
			//Director::getInstance()->replaceScene(LevelSelectScene::create(0));
		}
	});

	this->addChild(BackToMenuButton, 1);
}

void LevelSelectScene::GetNextLevelIDs(int CurrWorldNumber, int CurrLevelNumber, int& NextWorldNumber, int& NextLevelNumber)
{
	NextWorldNumber = -1;
	NextLevelNumber = -1;

	if (CurrLevelNumber + 1 < (int)LevelParamsContainer[CurrWorldNumber].size())
	{
		NextWorldNumber = CurrWorldNumber;
		NextLevelNumber = CurrLevelNumber + 1;
	}
	else if (CurrWorldNumber + 1 < (int)LevelParamsContainer.size())
	{
		NextWorldNumber = CurrWorldNumber + 1;
		NextLevelNumber = 0;
	}
}

void LevelSelectScene::GetPrevLevelIDs(int CurrWorldNumber, int CurrLevelNumber, int& PrevWorldNumber, int& PrevLevelNumber)
{
	PrevWorldNumber = -1;
	PrevLevelNumber = -1;

	if (CurrLevelNumber - 1 >= 0)
	{
		PrevWorldNumber = CurrWorldNumber;
		PrevLevelNumber = CurrLevelNumber - 1;
	}
	else if (CurrWorldNumber - 1 >= 0)
	{
		PrevWorldNumber = CurrWorldNumber - 1;
		PrevLevelNumber = LevelParamsContainer[PrevWorldNumber].size() - 1;
	}
}

const LevelParams& LevelSelectScene::GetNextLevelData(int CurrWorldNumber, int CurrLevelNumber)
{
	int NextWorldNumber, NextLevelNumber;
	GetNextLevelIDs(CurrWorldNumber, CurrLevelNumber, NextWorldNumber, NextLevelNumber);
	return LevelParamsContainer[NextWorldNumber][NextLevelNumber];
}

bool LevelSelectScene::CanTravelToNextLevel(int CurrWorldNumber, int CurrLevelNumber)
{
	bool bResult = false;

	if (CurrLevelNumber < STANDARD_LEVELS_PER_WORLD - 1)
	{
		int NextWorldNumber, NextLevelNumber;
		GetNextLevelIDs(CurrWorldNumber, CurrLevelNumber, NextWorldNumber, NextLevelNumber);

		if (NextWorldNumber != -1 && NextLevelNumber != -1)
			bResult = !LevelParamsContainer[NextWorldNumber][NextLevelNumber].bLocked;
	}
	else if (CurrLevelNumber != STANDARD_LEVELS_PER_WORLD - 1 && CurrLevelNumber != LEVELS_PER_WORLD - 1)
	{
		bResult = true;
	}

	return bResult;
}

void LevelSelectScene::NotifyLevelCompleted(int CurrWorldNumber, int CurrLevelNumber, int NumberOfStars)
{
	if (CurrLevelNumber < STANDARD_LEVELS_PER_WORLD - 1)
	{
		int NextWorldNumber, NextLevelNumber;

		GetNextLevelIDs(CurrWorldNumber, CurrLevelNumber, NextWorldNumber, NextLevelNumber);

		if (NextWorldNumber != -1 && NextLevelNumber != -1)
			LevelParamsContainer[NextWorldNumber][NextLevelNumber].bLocked = false;
	}
}
