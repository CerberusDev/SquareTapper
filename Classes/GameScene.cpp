// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameSquareStandard.h"
#include "GameSquareDoubleTap.h"
#include "LevelSelectScene.h"
#include "VerticalGameMask.h"
#include "HorizontalGameMask.h"
#include "StarImage.h"

USING_NS_CC;

GameScene::GameScene(LevelParams argLevelParamsStruct):
Mask(nullptr),
LevelParamsStruct(argLevelParamsStruct),
StartDelay(0.5f),
MaxTimeWithoutActiveSquare(0.5f),
SquarePositionMarginX(0.23f),
SquarePositionMarginY(0.2f),
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
    
    VisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<MenuItem*> MenuItems;

    auto BackItem = MenuItemImage::create("img/ui/Back_idle.png", "img/ui/Back_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(LevelSelectScene::create(LevelParamsStruct.WorldNumber));
	});
    
	BackItem->setPosition(Vec2(origin.x + VisibleSize.width * 0.77f, origin.y + VisibleSize.height * 0.07f));
	MenuItems.pushBack(BackItem);

	auto RestartItem = MenuItemImage::create("img/ui/Restart_idle.png", "img/ui/Restart_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(LevelParamsStruct));
	});

	RestartItem->setPosition(Vec2(origin.x + VisibleSize.width * 0.88f, origin.y + VisibleSize.height * 0.07f));
	MenuItems.pushBack(RestartItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	std::stringstream Stream;
	Stream << "Level " << LevelParamsStruct.LevelNumber;
	auto label = Label::createWithTTF(Stream.str(), "fonts/ADAM.CGPRO.ttf", FontSize);
	label->setPosition(Vec2(VisibleSize.width * 0.23f,  VisibleSize.height * 0.92f));
	this->addChild(label, 1);

    auto sprite = Sprite::create("img/ui/HelloWorld.png");
    sprite->setPosition(Vec2(VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);

	for (int i = 0; i < MAX_STARS_NUMBER; ++i)
		StarImages[i] = new StarImage(this, Vec2(VisibleSize.width * (0.6f + 0.15f * i), VisibleSize.height * 0.93f));

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
		{
			Vec2 Pos = Vec2(GetScreenPositionX(x), GetScreenPositionY(y));

			int CurrentSquareIndex = y * SQUARE_AMOUNT_X + x + 1;
			auto DoubleTapIndexIt = std::find(LevelParamsStruct.DoubleTapSquareIndices.begin(), LevelParamsStruct.DoubleTapSquareIndices.end(), CurrentSquareIndex);

			if (DoubleTapIndexIt == LevelParamsStruct.DoubleTapSquareIndices.end())
				Squares[x][y] = new GameSquareStandard(this, Pos, x, y);
			else
				Squares[x][y] = new GameSquareDoubleTap(this, Pos, x, y);
		}
	}

	if (LevelParamsStruct.bSpawnGameMask)
	{
		if (LevelParamsStruct.bVerticalMask)
			Mask = new VerticalGameMask(this, LevelParamsStruct.bKillingMask);
		else
			Mask = new HorizontalGameMask(this, LevelParamsStruct.bKillingMask);
	}

	auto StartDelayAction = DelayTime::create(LevelParamsStruct.bSpawnGameMask ? StartDelay + 0.7f : StartDelay);
	auto ActivateFirstSquareAction = CallFunc::create([&]() {ActivateNextSquare(); });
	runAction(Sequence::create(StartDelayAction, ActivateFirstSquareAction, nullptr));

	CCLOG("Initialization end");

    return true;
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

float GameScene::GetScreenPositionX(int SquareIndexX) const
{
	return GetScreenPosition(SquareIndexX, SQUARE_AMOUNT_X, SquarePositionMarginX, VisibleSize.width);
}

float GameScene::GetScreenPositionY(int SquareIndexY) const
{
	return GetScreenPosition(SquareIndexY, SQUARE_AMOUNT_Y, SquarePositionMarginY, VisibleSize.height);
}

float GameScene::GetScreenPosition(int SquareIndex, int SquaresNumber, float SquarePositionMargin, float ScreenSize) const
{
	float PosMod = SquarePositionMargin + (float)SquareIndex / (SquaresNumber - 1) * (1.0f - 2.0f * SquarePositionMargin);
	return ScreenSize * PosMod;
}

GameSquare* GameScene::GetSquareForActivation() const
{
	std::vector<GameSquare*> AvailableSquares;

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
		{
			if (Squares[x][y]->CanBeActivated())
				AvailableSquares.push_back(Squares[x][y]);
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
		QueueNextSquareActivation(LevelParamsStruct.SquaresActivationTimeInterval);
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

		auto sprite = Sprite::create("img/ui/SmallFrame.png");
		sprite->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.55f));
		this->addChild(sprite, 4);

		float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
		auto label = Label::createWithTTF("You lost!", "fonts/ADAM.CGPRO.ttf", FontSize);
		label->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.55f));
		this->addChild(label, 5);
	}
}

void GameScene::LevelCompleted()
{
	bLevelFinished = true;

	if (Mask)
		Mask->RequestFinishAnimation();

	auto DelayAction = DelayTime::create(0.4f);
	auto ShowMessageAction = CallFunc::create([&]() {ShowLevelCompletedMessage(); });
	runAction(Sequence::create(DelayAction, ShowMessageAction, nullptr));

	std::stringstream StringStreamLevelKey;
	StringStreamLevelKey << "Level" << LevelParamsStruct.LevelNumber;

	UserDefault* UserDefaultData = UserDefault::getInstance();
	int LastBestStarsNumber = UserDefaultData->getIntegerForKey(StringStreamLevelKey.str().c_str(), 0);

	if (StarsNumber > LastBestStarsNumber)
	{
		UserDefaultData->setIntegerForKey(StringStreamLevelKey.str().c_str(), StarsNumber);
		UserDefaultData->flush();
	}
}

void GameScene::ShowLevelCompletedMessage()
{
	auto sprite = Sprite::create("img/ui/SmallFrame.png");
	sprite->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.55f));
	this->addChild(sprite, 4);

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	auto label = Label::createWithTTF("You win!", "fonts/ADAM.CGPRO.ttf", FontSize);
	label->setPosition(Vec2(VisibleSize.width * 0.5f, VisibleSize.height * 0.55f));
	this->addChild(label, 5);
}