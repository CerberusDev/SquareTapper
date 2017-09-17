// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameSquareSequence.h"
#include "LevelSelectScene.h"
#include "VerticalGameMask.h"
#include "HorizontalGameMask.h"
#include "StarImage.h"

USING_NS_CC;

#define BLINK_TEXTURES_SIZE 512.0f
#define BUTTON_TEXTURES_SIZE 512.0f
#define BUTTON_SPRITE_SIZE 100.0f

#define BOTTOM_SQUARES_POS_Y 200.0f
#define DIST_BETWEEN_SQUARES 190.0f
#define LABELS_POS_Y 1195.0f
#define BUTTONS_POS_Y (BOTTOM_SQUARES_POS_Y - SQUARE_SPRITE_SIZE * 0.5f) * 0.5f
#define STARS_POS_Y 1125.0f

GameScene::GameScene(LevelParams argLevelParamsStruct):
BackMenuItem(nullptr),
RestartMenuItem(nullptr),
NextMenuItem(nullptr),
Mask(nullptr),
NextSequenceSquareToActivate(nullptr),
LevelParamsStruct(argLevelParamsStruct),
StartDelay(0.5f),
MaxTimeWithoutActiveSquare(0.5f),
SequenceSquaresActivationTimeInterval(0.15f),
UnactivatedSquaresNumber(SQUARE_AMOUNT_X * SQUARE_AMOUNT_Y),
StarsNumber(MAX_STARS_NUMBER),
bLevelFinished(false)
{

}

GameScene* GameScene::create(LevelParams argLevelParamsStruct)
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

	BackMenuItem->setPosition(Vec2(GetScreenPositionX(0), BUTTONS_POS_Y));
	BackMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	MenuItems.pushBack(BackMenuItem);

	RestartMenuItem = MenuItemImage::create("gui/icons/icon_replay_inactive_512.png", "img/ui/icon_replay_inactive_512.png",
		[&](Ref* sender) {
#ifdef _WINDOWS
		LevelSelectScene::InitializeLevelParams();
#endif
		Director::getInstance()->replaceScene(GameScene::create(LevelParamsStruct));
	});

	RestartMenuItem->setPosition(Vec2(GetScreenPositionX(2), BUTTONS_POS_Y));
	RestartMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
	MenuItems.pushBack(RestartMenuItem);

	auto const& LevelData = LevelSelectScene::GetLevelData();

	if (LevelData.back().back().LevelDisplayNumber != LevelParamsStruct.LevelDisplayNumber)
	{
		NextMenuItem = MenuItemImage::create("gui/icons/icon_arrow_inactive_512.png", "img/ui/icon_arrow_inactive_512.png",
			[&](Ref* sender) {
			if ((int)LevelData[LevelParamsStruct.WorldNumber].size() > LevelParamsStruct.LevelNumber + 1)
				Director::getInstance()->replaceScene(GameScene::create(LevelData[LevelParamsStruct.WorldNumber][LevelParamsStruct.LevelNumber + 1]));
			else
				Director::getInstance()->replaceScene(GameScene::create(LevelData[LevelParamsStruct.WorldNumber + 1][0]));
		});

		NextMenuItem->setPosition(Vec2(GetScreenPositionX(1), BUTTONS_POS_Y));
		NextMenuItem->setScale(BUTTON_SPRITE_SIZE / BUTTON_TEXTURES_SIZE);
		MenuItems.pushBack(NextMenuItem);
	}

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	float LevelLabelFontSize = 50.0f;
	std::stringstream LevelLabelStream;
	LevelLabelStream << "Lv " << LevelParamsStruct.LevelDisplayNumber;
	auto LevelLabel = Label::createWithTTF(LevelLabelStream.str(), FONT_FILE_PATH_STANDARD, LevelLabelFontSize);
	LevelLabel->setPosition(Vec2(GetScreenPositionX(1), LABELS_POS_Y));
	LevelLabel->setColor(Color3B(120, 115, 109));
	this->addChild(LevelLabel, 1);

	const std::string LevelAttemptsKey = GetLevelAttemptsKey(LevelParamsStruct.LevelDisplayNumber);
	int AttemptsNumber = UserDefault::getInstance()->getIntegerForKey(LevelAttemptsKey.c_str(), 0);
	++AttemptsNumber;
	UserDefault::getInstance()->setIntegerForKey(LevelAttemptsKey.c_str(), AttemptsNumber);

	float AttemptsNrLabelFontSize = 30.0f;
	std::stringstream AttemptsNrLabelStream;
	AttemptsNrLabelStream << "." << AttemptsNumber;
	auto AttemptsNrLabel = Label::createWithTTF(AttemptsNrLabelStream.str(), FONT_FILE_PATH_STANDARD, AttemptsNrLabelFontSize);
	AttemptsNrLabel->setPosition(Vec2(GetScreenPositionX(2), LABELS_POS_Y));
	AttemptsNrLabel->setColor(Color3B(120, 115, 109));
	this->addChild(AttemptsNrLabel, 1);

	const std::string LevelRecordKey = GetLevelRecordKey(LevelParamsStruct.LevelDisplayNumber);
	int RecordStarsNumber = UserDefault::getInstance()->getIntegerForKey(LevelRecordKey.c_str(), 0);

	for (int i = 0; i < MAX_STARS_NUMBER; ++i)
		StarImages[i] = new StarImage(this, Vec2(GetScreenPositionX(i), STARS_POS_Y), i >= MAX_STARS_NUMBER - RecordStarsNumber);

	SpawnGameObjects();

	auto StartDelayAction = DelayTime::create(LevelParamsStruct.bSpawnGameMask ? StartDelay + 0.7f : StartDelay);
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

	if (LevelParamsStruct.bSpawnGameMask)
	{
		if (LevelParamsStruct.bVerticalMask)
			Mask = new VerticalGameMask(this, LevelParamsStruct.bKillingMask);
		else
			Mask = new HorizontalGameMask(this, LevelParamsStruct.bKillingMask);
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

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
			delete Squares[x][y];

	if (Mask)
		delete Mask;

	for (int i = 0; i < MAX_STARS_NUMBER; ++i)
		delete StarImages[i];
}

float GameScene::GetScreenPositionX(int SquareIndexX)
{
	const float Margin = (DESIGN_RES_X - DIST_BETWEEN_SQUARES * (SQUARE_AMOUNT_X - 1)) / 2.0f;
	return Margin + DIST_BETWEEN_SQUARES * SquareIndexX;
}

float GameScene::GetScreenPositionY(int SquareIndexY)
{
	return BOTTOM_SQUARES_POS_Y + DIST_BETWEEN_SQUARES * SquareIndexY;
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
		--UnactivatedSquaresNumber;
	}

	if (UnactivatedSquaresNumber > 0)
	{
		float NextActivationDelay;

		if (NextSequenceSquareToActivate != nullptr)
			NextActivationDelay = SequenceSquaresActivationTimeInterval;
		else
			NextActivationDelay = LevelParamsStruct.SquaresActivationTimeInterval;

		QueueNextSquareActivation(NextActivationDelay);
	}
}

void GameScene::QueueNextSquareActivation(float Delay)
{
	auto DelayAction = DelayTime::create(Delay);
	auto ActivateNextSquareAction = CallFunc::create([&]() {ActivateNextSquare(); });
	auto MySequence = Sequence::create(DelayAction, ActivateNextSquareAction, nullptr);
	MySequence->setTag(ACTIVATION_SEQUENCE_ACTION_TAG);
	runAction(MySequence);
}

void GameScene::OnSquareCompleted(GameSquare* CompletedSquare)
{
	ActiveSquares.erase(std::remove(ActiveSquares.begin(), ActiveSquares.end(), CompletedSquare));

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
		else
		{
			LevelCompleted();
		}
	}
}

void GameScene::OnSquareFailed(GameSquare* FailedSquare)
{
	ActiveSquares.erase(std::remove(ActiveSquares.begin(), ActiveSquares.end(), FailedSquare));

	DecreaseStarNumber();

	if (!bLevelFinished && ActiveSquares.empty() && UnactivatedSquaresNumber == 0)
		LevelCompleted();
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
	
		if (Mask)
			Mask->RequestFinishAnimation();

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);

		RestartMenuItem->setNormalImage(Sprite::create("gui/icons/icon_replay_active_512.png"));
	}
}

void GameScene::LevelCompleted()
{
	bLevelFinished = true;
	Blink("gui/squares/square_active_512.png");

	if (Mask)
		Mask->RequestFinishAnimation();

	std::string LevelKey = GetLevelRecordKey(LevelParamsStruct.LevelDisplayNumber);

	UserDefault* UserDefaultData = UserDefault::getInstance();
	int LastBestStarsNumber = UserDefaultData->getIntegerForKey(LevelKey.c_str(), 0);

	if (StarsNumber > LastBestStarsNumber)
	{
		UserDefaultData->setIntegerForKey(LevelKey.c_str(), StarsNumber);
		UserDefaultData->flush();
	}

	if (NextMenuItem)
		NextMenuItem->setNormalImage(Sprite::create("gui/icons/icon_arrow_active_512.png"));
}

void GameScene::Blink(const std::string& SpriteFilePath)
{
	auto BlinkSprite = Sprite::create(SpriteFilePath);
	BlinkSprite->setOpacity(0.0f);
	BlinkSprite->setPosition(DESIGN_RES_X / 2.0f, DESIGN_RES_Y / 2.0f);
	BlinkSprite->setScale(DESIGN_RES_X / BLINK_TEXTURES_SIZE, DESIGN_RES_Y / BLINK_TEXTURES_SIZE);
	addChild(BlinkSprite, 30);

	auto FadeInAction = FadeTo::create(0.08f, 160);
	auto FadeOutAction = FadeTo::create(0.12f, 0);
	auto RemoveMyself = CallFunc::create([BlinkSprite]() {
		BlinkSprite->removeFromParent();
	});

	BlinkSprite->runAction(Sequence::create(FadeInAction, FadeOutAction, RemoveMyself, nullptr));
}
