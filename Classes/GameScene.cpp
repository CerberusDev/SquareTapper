// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameSquareSequence.h"
#include "LevelSelectScene.h"
#include "VerticalGameMask.h"
#include "HorizontalGameMask.h"
#include "ToggleGameMask.h"
#include "StarImage.h"

USING_NS_CC;

#define BOTTOM_SQUARES_POS_Y 200.0f
#define DIST_BETWEEN_SQUARES 190.0f
#define LABELS_POS_Y 1190.0f
#define BUTTONS_POS_Y (BOTTOM_SQUARES_POS_Y - SQUARE_SPRITE_SIZE * 0.5f) * 0.5f
#define STARS_POS_Y 1110.0f

GameScene::GameScene(const LevelParams& argLevelParamsStruct):
BackMenuItem(nullptr),
RestartMenuItem(nullptr),
NextMenuItem(nullptr),
NextSequenceSquareToActivate(nullptr),
LevelParamsStruct(argLevelParamsStruct),
StartDelay(0.5f),
MaxTimeWithoutActiveSquare(0.5f),
SequenceSquaresActivationTimeInterval(0.15f),
NumberOfFinishedSquares(0),
StarsNumber(MAX_STARS_NUMBER),
bLevelFinished(false)
{

}

GameScene* GameScene::create(const LevelParams& argLevelParamsStruct)
{
	GameScene *pRet = new(std::nothrow) GameScene(argLevelParamsStruct);

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

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	Vector<MenuItem*> MenuItems;

	BackMenuItem = MenuItemImage::create("gui/icons/icon_menu_inactive_512.png", "img/ui/icon_menu_inactive_512.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(LevelSelectScene::create(LevelParamsStruct.WorldNumber));
	});

	BackMenuItem->setPosition(Vec2(GetScreenPositionX(0), GetButtonsPositionY()));
	BackMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	MenuItems.pushBack(BackMenuItem);

	RestartMenuItem = MenuItemImage::create("gui/icons/icon_replay_inactive_512.png", "img/ui/icon_replay_inactive_512.png",
		[&](Ref* sender) {
#ifdef _WINDOWS
		LevelSelectScene::InitializeLevelParams();
#endif
		Director::getInstance()->replaceScene(GameScene::create(LevelParamsStruct));
	});

	RestartMenuItem->setPosition(Vec2(GetScreenPositionX(2), GetButtonsPositionY()));
	RestartMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	MenuItems.pushBack(RestartMenuItem);

	auto const& LevelData = LevelSelectScene::GetLevelData();

	NextMenuItem = MenuItemImage::create("gui/icons/icon_arrow_inactive_512.png", "img/ui/icon_arrow_inactive_512.png",
		[&](Ref* sender) {
		const LevelParams& NextLevelParams = LevelSelectScene::GetNextLevelData(LevelParamsStruct.WorldNumber, LevelParamsStruct.LevelNumber);
		Director::getInstance()->replaceScene(GameScene::create(NextLevelParams));
	});

	if (LevelSelectScene::IsNextLevelLocked(LevelParamsStruct.WorldNumber, LevelParamsStruct.LevelNumber))
		NextMenuItem->setVisible(false);

	NextMenuItem->setPosition(Vec2(GetScreenPositionX(1), GetButtonsPositionY()));
	NextMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	MenuItems.pushBack(NextMenuItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	float LevelLabelFontSize = 60.0f;
	std::stringstream LevelLabelStream;
	LevelLabelStream << "Lv " << LevelParamsStruct.LevelDisplayNumber;
	auto LevelLabel = Label::createWithTTF(LevelLabelStream.str(), FONT_FILE_PATH_STANDARD, LevelLabelFontSize);
	LevelLabel->setPosition(Vec2(GetScreenPositionX(1), GetLabelsPositionY()));
	LevelLabel->setColor(GREY_COLOR);
	this->addChild(LevelLabel, 1);

	const std::string LevelAttemptsKey = GetLevelAttemptsKey(LevelParamsStruct.LevelDisplayNumber);
	int AttemptsNumber = UserDefault::getInstance()->getIntegerForKey(LevelAttemptsKey.c_str(), 0);
	++AttemptsNumber;
	UserDefault::getInstance()->setIntegerForKey(LevelAttemptsKey.c_str(), AttemptsNumber);

	float AttemptsNrLabelFontSize = 40.0f;
	std::stringstream AttemptsNrLabelStream;
	AttemptsNrLabelStream << "." << AttemptsNumber;
	auto AttemptsNrLabel = Label::createWithTTF(AttemptsNrLabelStream.str(), FONT_FILE_PATH_STANDARD, AttemptsNrLabelFontSize);
	AttemptsNrLabel->setPosition(Vec2(GetScreenPositionX(MAX_STARS_NUMBER - 1), GetLabelsPositionY()));
	AttemptsNrLabel->setColor(GREY_COLOR);
	this->addChild(AttemptsNrLabel, 1);

	float DebugLabelsFontSize = 22.0f;

	std::stringstream DebugWorldStream;
	DebugWorldStream << "World_" << LevelParamsStruct.WorldNumber;
	auto DebugWorldLabel = Label::createWithTTF(DebugWorldStream.str(), FONT_FILE_PATH_STANDARD, DebugLabelsFontSize);
	DebugWorldLabel->setPosition(Vec2(80.0f, 1235.0f));
	DebugWorldLabel->setColor(Color3B::RED);
	this->addChild(DebugWorldLabel, 1);

	std::stringstream DebugLevelStream;
	DebugLevelStream << "Level: " << LevelParamsStruct.LevelNumber + 1;
	auto DebugLevelLabel = Label::createWithTTF(DebugLevelStream.str(), FONT_FILE_PATH_STANDARD, DebugLabelsFontSize);
	DebugLevelLabel->setPosition(Vec2(80.0f, 1200.0f));
	DebugLevelLabel->setColor(Color3B::RED);
	this->addChild(DebugLevelLabel, 1);

	const std::string LevelRecordKey = GetLevelRecordKey(LevelParamsStruct.LevelDisplayNumber);
	int RecordStarsNumber = UserDefault::getInstance()->getIntegerForKey(LevelRecordKey.c_str(), 0);

	for (int i = 0; i < MAX_STARS_NUMBER; ++i)
		StarImages[i] = new StarImage(this, Vec2(GetScreenPositionX(i), GetStarPositionY()), i >= MAX_STARS_NUMBER - RecordStarsNumber);

	SpawnGameObjects();

	auto StartDelayAction = DelayTime::create(LevelParamsStruct.Masks.size() > 0 ? StartDelay + 0.7f : StartDelay);
	auto ActivateFirstSquareAction = CallFunc::create([&]() {ActivateNextSquare(); });
	runAction(Sequence::create(StartDelayAction, ActivateFirstSquareAction, nullptr));

	CCLOG("Initialization end");

	return true;
}

void GameScene::SpawnGameObjects()
{
	std::vector<int> SafeSquareIndices;
	std::vector<int> DangerousSquareIndices;
	std::vector<int> DangerousSecondTapSquareIndices;

	if (LevelParamsStruct.DangerousSecondTapSquaresNumber > 0)
	{
		DangerousSecondTapSquareIndices = LevelParamsStruct.DoubleTapSquareIndices;
		std::random_shuffle(DangerousSecondTapSquareIndices.begin(), DangerousSecondTapSquareIndices.end());
		DangerousSecondTapSquareIndices.resize(LevelParamsStruct.DangerousSecondTapSquaresNumber);
	}

	if (LevelParamsStruct.DangerousSquaresNumber > 0)
	{
		for (int i = 1; i <= SQUARE_AMOUNT_X * SQUARE_AMOUNT_Y; ++i)
			if (!VectorContains(DangerousSecondTapSquareIndices, i))
				DangerousSquareIndices.push_back(i);

		std::random_shuffle(DangerousSquareIndices.begin(), DangerousSquareIndices.end());
		DangerousSquareIndices.resize(LevelParamsStruct.DangerousSquaresNumber);
	}

	if (LevelParamsStruct.SafeSquaresNumber > 0)
	{
		for (int i = 1; i <= SQUARE_AMOUNT_X * SQUARE_AMOUNT_Y; ++i)
			if (!VectorContains(DangerousSecondTapSquareIndices, i) && !VectorContains(DangerousSquareIndices, i))
				SafeSquareIndices.push_back(i);

		std::random_shuffle(SafeSquareIndices.begin(), SafeSquareIndices.end());
		SafeSquareIndices.resize(LevelParamsStruct.SafeSquaresNumber);
	}

	ModifiedSequencesSquareIndices = LevelParamsStruct.SequencesSquareIndices;

	for (std::vector<int>& CurrSequenceIndices : ModifiedSequencesSquareIndices)
		if (rand() % 2 == 0)
			std::reverse(CurrSequenceIndices.begin(), CurrSequenceIndices.end());

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
			SpawnSingleGameSquare(x, y, SafeSquareIndices, DangerousSquareIndices, DangerousSecondTapSquareIndices);

	for (const MaskDefiniton& CurrMaskDefinition : LevelParamsStruct.Masks)
	{
		switch (CurrMaskDefinition.Type)
		{
		case EMaskType::Vertical:
			Masks.push_back(new VerticalGameMask(this, CurrMaskDefinition.bKillingMask));
			break;
		case EMaskType::Horizontal:
			Masks.push_back(new HorizontalGameMask(this, CurrMaskDefinition.bKillingMask));
			break;
		case EMaskType::HorizontalBig:
			Masks.push_back(new HorizontalGameMask(this, CurrMaskDefinition.bKillingMask, 0));
			Masks.push_back(new HorizontalGameMask(this, CurrMaskDefinition.bKillingMask, 1));
			break;
		case EMaskType::Chessboard:
			for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
				for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
					Masks.push_back(new ToggleGameMask(this, CurrMaskDefinition.bKillingMask, Vec2(x, y), Vec2(1, 1), (x + y) % 2 == 0));
			break;
		}
	}
}

void GameScene::SpawnSingleGameSquare(int x, int y, const std::vector<int>& SafeSquareIndices, const std::vector<int>& DangerousSquareIndices, const std::vector<int>& DangerousSecondTapSquareIndices)
{
	const int SquareIndex = y * SQUARE_AMOUNT_X + x + 1;
	const Vec2 ScreepPos = Vec2(GetScreenPositionX(x), GetScreenPositionY(y));
	const bool bDoubleTapSquare = VectorContains(LevelParamsStruct.DoubleTapSquareIndices, SquareIndex) || VectorContains(LevelParamsStruct.SequenceDoubleTapSquareIndices, SquareIndex);
	bool bSequenceSquare = false;
	bool bFirstInSequecne = false;
	int NextSquareInSequenceIndex = -1;

	for (const std::vector<int>& CurrSequenceIndices : ModifiedSequencesSquareIndices)
	{
		for (unsigned int i = 0; i < CurrSequenceIndices.size(); ++i)
		{
			if (CurrSequenceIndices[i] == SquareIndex)
			{
				bSequenceSquare = true;

				if (i == 0)
					bFirstInSequecne = true;

				if (i + 1 < CurrSequenceIndices.size())
					NextSquareInSequenceIndex = CurrSequenceIndices[i + 1];
			}
		}
	}

	ESquareSafetyType SquareSafetyTape = ESquareSafetyType::Standard;

	if (VectorContains(DangerousSquareIndices, SquareIndex))
		SquareSafetyTape = ESquareSafetyType::Dangerous;
	else if (VectorContains(SafeSquareIndices, SquareIndex))
		SquareSafetyTape = ESquareSafetyType::Safe;
	else if (bDoubleTapSquare && VectorContains(DangerousSecondTapSquareIndices, SquareIndex))
		SquareSafetyTape = ESquareSafetyType::DangerousSecondTap;

	if (bSequenceSquare)
	{
		GameSquareSequence* NewSequenceSquare = new GameSquareSequence(this, bDoubleTapSquare, SquareSafetyTape, ScreepPos, x, y);
		Squares[x][y] = NewSequenceSquare;

		if (bFirstInSequecne)
			NewSequenceSquare->SetAsNextToActivate();
		
		if (NextSquareInSequenceIndex != -1)
			NewSequenceSquare->SetNextSquareInSequenceIndex(NextSquareInSequenceIndex);
	}
	else
	{
		Squares[x][y] = new GameSquare(this, bDoubleTapSquare, SquareSafetyTape, ScreepPos, x, y);
	}
}

void GameScene::onExit()
{
	Scene::onExit();

	for (unsigned int x = 0; x < SQUARE_AMOUNT_X; ++x)
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
			delete Squares[x][y];

	for (unsigned int i = 0; i < Masks.size(); ++i)
		delete Masks[i];

	for (unsigned int i = 0; i < MAX_STARS_NUMBER; ++i)
		delete StarImages[i];
}

float GameScene::GetScreenPositionX(int SquareIndexX)
{
	const float Margin = (DESIGN_RES_X - GetDistBetweenSquares() * (SQUARE_AMOUNT_X - 1)) / 2.0f;
	return Margin + GetDistBetweenSquares() * SquareIndexX;
}

float GameScene::GetScreenPositionY(int SquareIndexY)
{
	return BOTTOM_SQUARES_POS_Y + GetDistBetweenSquares() * SquareIndexY;
}

float GameScene::GetStarPositionY()
{
	return STARS_POS_Y;
}

float GameScene::GetLabelsPositionY()
{
	return LABELS_POS_Y;
}

float GameScene::GetButtonsPositionY()
{
	return BUTTONS_POS_Y;
}

float GameScene::GetDistBetweenSquares()
{
	return DIST_BETWEEN_SQUARES;
}

GameSquare* GameScene::GetSquareByIndex(int Index) const
{
	int x = (Index - 1) % SQUARE_AMOUNT_X;
	int y = (Index - 1) / SQUARE_AMOUNT_X;
	return Squares[x][y];
}

void GameScene::SetNextSequenceSquareToActivate(int SquareIndex)
{
	NextSequenceSquareToActivate = dynamic_cast<GameSquareSequence*>(GetSquareByIndex(SquareIndex));
	NextSequenceSquareToActivate->SetAsNextToActivate();
}

GameSquare* GameScene::GetSquareForActivation()
{
	std::vector<GameSquare*> AvailableSquares;

	if (NextSequenceSquareToActivate != nullptr)
	{
		if (NextSequenceSquareToActivate->CanBeActivated())
		{
			AvailableSquares.push_back(NextSequenceSquareToActivate);
			NextSequenceSquareToActivate = nullptr;
		}
	}
	else
	{
		for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
		{
			for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
			{
				if (Squares[x][y]->CanBeActivated())
					AvailableSquares.push_back(Squares[x][y]);
			}
		}
	}

	std::random_shuffle(AvailableSquares.begin(), AvailableSquares.end());
	return AvailableSquares.size() > 0 ? AvailableSquares[0] : nullptr;
}

void GameScene::ActivateNextSquare()
{
	if (GameSquare* NextSquare = GetSquareForActivation())
	{
		NextSquare->StartActivation(LevelParamsStruct.TotalSquareActivationTime);
		ActiveSquares.push_back(NextSquare);
	}

	float NextActivationDelay;

	if (NextSequenceSquareToActivate != nullptr)
		NextActivationDelay = SequenceSquaresActivationTimeInterval;
	else
		NextActivationDelay = LevelParamsStruct.SquaresActivationTimeInterval;

	QueueNextSquareActivation(NextActivationDelay);
}

void GameScene::QueueNextSquareActivation(float Delay)
{
	auto DelayAction = DelayTime::create(Delay);
	auto ActivateNextSquareAction = CallFunc::create([&]() {ActivateNextSquare(); });
	auto MySequence = Sequence::create(DelayAction, ActivateNextSquareAction, nullptr);
	MySequence->setTag(ACTIVATION_SEQUENCE_ACTION_TAG);
	runAction(MySequence);
}

void GameScene::OnSquareCompleted(GameSquare* CompletedSquare, bool bWillBeActivatingAgain)
{
	ActiveSquares.erase(std::remove(ActiveSquares.begin(), ActiveSquares.end(), CompletedSquare));

	if (!bWillBeActivatingAgain)
		++NumberOfFinishedSquares;

	if (ActiveSquares.empty())
	{
		auto ActionManager = Director::getInstance()->getActionManager();
		auto ReturnedAction = ActionManager->getActionByTag(ACTIVATION_SEQUENCE_ACTION_TAG, this);

		if (Sequence* ReturnedSequence = dynamic_cast<Sequence*>(ReturnedAction))
		{
			const float SequenceRemainingTime = ReturnedSequence->getDuration() - ReturnedSequence->getElapsed();

			if (SequenceRemainingTime > MaxTimeWithoutActiveSquare)
			{
				ActionManager->removeAllActionsFromTarget(this);
				QueueNextSquareActivation(MaxTimeWithoutActiveSquare);
			}
		}

		CheckIfLevelCompleted();
	}
}

void GameScene::CheckIfLevelCompleted()
{
	if (NumberOfFinishedSquares == SQUARE_AMOUNT_X * SQUARE_AMOUNT_Y)
		LevelCompleted();
}

void GameScene::OnSquareFailed(GameSquare* FailedSquare)
{
	ActiveSquares.erase(std::remove(ActiveSquares.begin(), ActiveSquares.end(), FailedSquare));

	++NumberOfFinishedSquares;
	DecreaseStarNumber();

	if (!bLevelFinished)
		CheckIfLevelCompleted();
}

void GameScene::DecreaseStarNumber()
{
	StarImages[MAX_STARS_NUMBER - StarsNumber]->Inactivate();
	--StarsNumber;
	Blink("gui/squares/square_star_512.png");

	if (StarsNumber == 0)
		LevelFailed();
}

void GameScene::LevelFailed()
{
	if (!bLevelFinished)
	{
		bLevelFinished = true;

		for (GameSquare* CurrSquare : ActiveSquares)
			CurrSquare->PauseOnGameOver();
	
		for (GameMask* CurrMask : Masks)
			CurrMask->RequestFinishAnimation();

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);

		RestartMenuItem->setNormalImage(Sprite::create("gui/icons/icon_replay_active_512.png"));
	}
}

void GameScene::LevelCompleted()
{
	bLevelFinished = true;
	Blink("gui/squares/square_active_512.png");

	for (GameMask* CurrMask : Masks)
		CurrMask->RequestFinishAnimation();

	std::string LevelKey = GetLevelRecordKey(LevelParamsStruct.LevelDisplayNumber);

	UserDefault* UserDefaultData = UserDefault::getInstance();
	int LastBestStarsNumber = UserDefaultData->getIntegerForKey(LevelKey.c_str(), 0);

	if (StarsNumber > LastBestStarsNumber)
	{
		UserDefaultData->setIntegerForKey(LevelKey.c_str(), StarsNumber);
		UserDefaultData->flush();
	
		LevelSelectScene::NotifyLevelCompleted(LevelParamsStruct.WorldNumber, LevelParamsStruct.LevelNumber, StarsNumber);
	}

	if (!LevelSelectScene::IsNextLevelLocked(LevelParamsStruct.WorldNumber, LevelParamsStruct.LevelNumber))
	{
		NextMenuItem->setVisible(true);
		NextMenuItem->setNormalImage(Sprite::create("gui/icons/icon_arrow_active_512.png"));
	}
}

void GameScene::Blink(const std::string& SpriteFilePath)
{
	auto BlinkSprite = Sprite::create(SpriteFilePath);
	BlinkSprite->setOpacity(0.0f);
	BlinkSprite->setPosition(DESIGN_RES_X / 2.0f, DESIGN_RES_Y / 2.0f);
	BlinkSprite->setScale(DESIGN_RES_X / SQUARE_TEXTURES_SIZE, DESIGN_RES_Y / SQUARE_TEXTURES_SIZE);
	addChild(BlinkSprite, 30);

	auto FadeInAction = FadeTo::create(0.08f, 160);
	auto FadeOutAction = FadeTo::create(0.12f, 0);
	auto RemoveMyself = CallFunc::create([BlinkSprite]() {
		BlinkSprite->removeFromParent();
	});

	BlinkSprite->runAction(Sequence::create(FadeInAction, FadeOutAction, RemoveMyself, nullptr));
}
