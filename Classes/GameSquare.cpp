// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameSquare::GameSquare(Scene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY, const std::string& InactiveSpriteFilename, const std::string& ActivationSpriteFilename):
PosX(argPosX),
PosY(argPosY),
ParentScene(argScene),
EventListener(nullptr),
InactiveSprite(nullptr),
ActivationSprite(nullptr),
FailedSprite(nullptr),
CompletedSprite(nullptr),
SpritePosition(argSpritePosition),
State(ESquareState::Inactive),
SavedActivationTotalTime(-1.0f),
CompletedSpriteFadeInTime(0.15f),
ActivationFreezeRequestsCounter(0),
bBlockTouchEvents(false),
bPausedOnGameOver(false)
{
	InactiveSprite = Sprite::create(InactiveSpriteFilename);
	InactiveSprite->setPosition(SpritePosition);
	ParentScene->addChild(InactiveSprite, 1);

	EventListener = EventListenerTouchOneByOne::create();
	EventListener->setSwallowTouches(true);
	EventListener->onTouchBegan = [&](Touch* touch, Event* event) {
		Vec2 p = touch->getLocation();
		Rect rect = InactiveSprite->getBoundingBox();

		if (rect.containsPoint(p))
		{
			OnTouch(touch, event);
			return true;
		}
		else
		{
			return false;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(EventListener, 2);

	ActivationSprite = Sprite::create(ActivationSpriteFilename);
	ActivationSprite->setPosition(SpritePosition);
	ActivationSprite->setScale(0.0f);
	ParentScene->addChild(ActivationSprite, 2);
}

GameSquare::~GameSquare()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(EventListener);

	InactiveSprite->removeFromParent();
	ActivationSprite->removeFromParent();

	if (FailedSprite)
		FailedSprite->removeFromParent();

	if (CompletedSprite)
		CompletedSprite->removeFromParent();
}

void GameSquare::StartActivation(float ActivationTotalTime)
{
	SavedActivationTotalTime = ActivationTotalTime;
	State = ESquareState::DuringActivation;

	auto ScaleAction = ScaleTo::create(ActivationTotalTime, 1.0f);
	auto EndFunc = CallFunc::create([&]() { ActivationEnded(); });

	ActivationSprite->runAction(Sequence::create(ScaleAction, EndFunc, nullptr));
}

void GameSquare::OnTouch(Touch* touch, Event* event)
{
	if (State == ESquareState::DuringActivation && !bBlockTouchEvents && !bPausedOnGameOver)
		SquareCorrectlyTapped();
}

void GameSquare::SimulateCorrectTap()
{
	SquareCorrectlyTapped();
}

void GameSquare::SquareCorrectlyTapped()
{
	State = ESquareState::Completed;

	CompletedSprite = Sprite::create("img/squares/SquareCompleted.png");
	CompletedSprite->setPosition(SpritePosition);
	CompletedSprite->setOpacity(0.0f);
	CompletedSprite->setScale(ActivationSprite->getScale());
	ParentScene->addChild(CompletedSprite, 3);

	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);

	auto ScaleSequence = ScaleUpActivationSquare();

	auto FadeInAction = FadeIn::create(CompletedSpriteFadeInTime);
	CompletedSprite->runAction(Spawn::createWithTwoActions(FadeInAction, ScaleSequence->clone()));

	if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
		ParentGameScene->OnSquareCompleted(this);
}

Sequence* GameSquare::ScaleUpActivationSquare()
{
	auto ScaleAction1 = ScaleTo::create(0.04f, 1.0f);
	auto ScaleAction2 = ScaleTo::create(0.04f, 1.1f);
	auto ScaleAction3 = ScaleTo::create(0.07f, 1.0f);
	auto ScaleSequence = Sequence::create(ScaleAction1, ScaleAction2, ScaleAction3, nullptr);
	ActivationSprite->runAction(ScaleSequence);

	return ScaleSequence;
}

void GameSquare::ActivationEnded()
{
	Failed();
}

void GameSquare::Failed()
{
	State = ESquareState::Failed;

	if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
		ParentGameScene->OnSquareFailed(this);

	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);

	FailedSprite = Sprite::create("img/squares/SquareFailed.png");
	FailedSprite->setPosition(SpritePosition);
	FailedSprite->setOpacity(0.0f);
	ParentScene->addChild(FailedSprite, 3);

	auto FadeInAction = FadeIn::create(0.8f);
	FailedSprite->runAction(FadeInAction);
}

void GameSquare::SetActivationFreeze(bool argbActivationFrozen)
{
	int LastActivationFreezeRequestsCounter = ActivationFreezeRequestsCounter;
	int CounterMod = argbActivationFrozen ? 1 : -1;
	ActivationFreezeRequestsCounter += CounterMod;

	if (ActivationFreezeRequestsCounter < 0)
	{
		CCLOG("Oh, well, that's not good: ActivationFreezeRequestsCounter is smaller than 0!");
		ActivationFreezeRequestsCounter = 0;
	}

	if (State == ESquareState::DuringActivation)
	{
		if (ActivationFreezeRequestsCounter == 0)
			Director::getInstance()->getActionManager()->resumeTarget(ActivationSprite);
		else if (LastActivationFreezeRequestsCounter == 0)
			Director::getInstance()->getActionManager()->pauseTarget(ActivationSprite);
	}
}

void GameSquare::SetBlockTouchEvents(bool argbBlockTouchEvents)
{
	bBlockTouchEvents = argbBlockTouchEvents;
}

void GameSquare::PauseOnGameOver()
{
	bPausedOnGameOver = true;
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);
}
