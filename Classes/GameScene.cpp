// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MySquare.h"
#include "LevelSelectScene.h"

USING_NS_CC;

GameScene::GameScene(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime):
LevelNumber(argLevelNumber),
StartDelay(0.5f),
MaxTimeWithoutActiveSquare(0.5f),
TimeBetweenSquaresActivation(argTimeBetweenSquaresActivation),
SquareActivationTotalTime(argSquareActivationTotalTime),
ActiveSquaresNumber(0)
{

}

GameScene* GameScene::create(int argLevelNumber, float argTimeBetweenSquaresActivation, float argSquareActivationTotalTime)
{
	GameScene *pRet = new(std::nothrow) GameScene(argLevelNumber, argTimeBetweenSquaresActivation, argSquareActivationTotalTime);

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<MenuItem*> MenuItems;

    auto BackItem = MenuItemImage::create("Back_idle.png", "Back_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(LevelSelectScene::create());
	});
    
	BackItem->setPosition(Vec2(origin.x + visibleSize.width * 0.77f, origin.y + visibleSize.height * 0.07f));
	MenuItems.pushBack(BackItem);

	auto RestartItem = MenuItemImage::create("Restart_idle.png", "Restart_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(LevelNumber, TimeBetweenSquaresActivation, SquareActivationTotalTime));
	});

	RestartItem->setPosition(Vec2(origin.x + visibleSize.width * 0.88f, origin.y + visibleSize.height * 0.07f));
	MenuItems.pushBack(RestartItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
    auto label = Label::createWithTTF("Tap the squares!", "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height * 0.955f));
	this->addChild(label, 1);

	FontSize = 36.0f / Director::getInstance()->getContentScaleFactor();
	std::stringstream Stream;
	Stream << "Level " << LevelNumber;
	label = Label::createWithTTF(Stream.str(), "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height * 0.9f));
	this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);

	float OffsetX = 0.23f;
	float OffsetY = 0.2f;

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		float PosXMod = OffsetX + (float)x / (SQUARE_AMOUNT_X - 1) * (1.0f - 2.0f * OffsetX);

		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
		{
			float PosYMod = OffsetY + (float)y / (SQUARE_AMOUNT_Y - 1) * (1.0f - 2.0f * OffsetY);
			Vec2 Pos = Vec2(visibleSize.width * PosXMod + origin.x, visibleSize.height * PosYMod + origin.y);
			Squares[x][y] = new MySquare(this, Pos);
			AvailableSquares.push_back(std::pair<int, int>(x, y));
		}
	}

	std::random_shuffle(AvailableSquares.begin(), AvailableSquares.end());

	auto StartDelayAction = DelayTime::create(StartDelay);
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
}

void GameScene::ActivateNextSquare()
{
	std::pair<int, int> NextSquareCoords = AvailableSquares.back();
	Squares[NextSquareCoords.first][NextSquareCoords.second]->StartActivation(SquareActivationTotalTime);
	AvailableSquares.pop_back();
	++ActiveSquaresNumber;

	if (!AvailableSquares.empty())
		QueueNextSquareActivation(TimeBetweenSquaresActivation);
}

void GameScene::QueueNextSquareActivation(float Delay)
{
	auto DelayAction = DelayTime::create(Delay);
	auto ActivateNextSquareAction = CallFunc::create([&]() {ActivateNextSquare(); });
	auto MySequence = Sequence::create(DelayAction, ActivateNextSquareAction, nullptr);
	MySequence->setTag(ACTIVATION_SEQUENCE_ACTION_TAG);
	runAction(MySequence);
}

void GameScene::OnSquareCompleted()
{
	--ActiveSquaresNumber;

	if (ActiveSquaresNumber == 0)
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
	}
}

void GameScene::OnSquareFailed()
{
	Director::getInstance()->getActionManager()->pauseAllRunningActions();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("SmallFrame.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.55f));
	this->addChild(sprite, 2);

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	auto label = Label::createWithTTF("You lost!", "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.55f));
	this->addChild(label, 3);
}
