// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameSquare::GameSquare(GameScene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY):
PosX(argPosX),
PosY(argPosY),
ParentScene(argScene),
EventListener(nullptr),
InactiveSprite(nullptr),
ActivationSprite(nullptr),
FailedSprite(nullptr),
SpritePosition(argSpritePosition),
State(ESquareState::Inactive),
bActivationFrozen(false),
bBlockTouchEvents(false),
bPausedOnGameOver(false)
{
	InactiveSprite = Sprite::create("img/squares/SquareInactive.png");
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

	ActivationSprite = Sprite::create("img/squares/SquareActive.png");
	ActivationSprite->setPosition(SpritePosition);
	ActivationSprite->setScale(0.0f);
	ParentScene->addChild(ActivationSprite, 2);
}

GameSquare::~GameSquare()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(EventListener);
}

void GameSquare::StartActivation(float ActivationTotalTime)
{
	State = ESquareState::DuringActivation;

	auto ScaleAction = ScaleTo::create(ActivationTotalTime, 1.0f);
	auto EndFunc = CallFunc::create([&]() { Failed(); });

	ActivationSprite->runAction(Sequence::create(ScaleAction, EndFunc, nullptr));
}

void GameSquare::OnTouch(Touch* touch, Event* event)
{
	if (State == ESquareState::DuringActivation && !bBlockTouchEvents && !bPausedOnGameOver)
	{
		State = ESquareState::Completed;

		CompletedSprite = Sprite::create("img/squares/SquareCompleted.png");
		CompletedSprite->setPosition(SpritePosition);
		CompletedSprite->setOpacity(0.0f);
		CompletedSprite->setScale(ActivationSprite->getScale());
		ParentScene->addChild(CompletedSprite, 3);

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);

		auto ScaleAction1 = ScaleTo::create(0.075f, 1.0f);
		auto ScaleAction2 = ScaleTo::create(0.075f, 1.1f);
		auto ScaleAction3 = ScaleTo::create(0.15f, 1.0f);
		auto ScaleSequence = Sequence::create(ScaleAction1, ScaleAction2, ScaleAction3, nullptr);
		ActivationSprite->runAction(ScaleSequence);

		auto FadeInAction = FadeIn::create(0.3f);
		CompletedSprite->runAction(Spawn::createWithTwoActions(FadeInAction, ScaleSequence->clone()));

		ParentScene->OnSquareCompleted(this);
	}
}

void GameSquare::Failed()
{
	State = ESquareState::Failed;
	ParentScene->OnSquareFailed(this);

	FailedSprite = Sprite::create("img/squares/SquareFailed.png");
	FailedSprite->setPosition(SpritePosition);
	FailedSprite->setOpacity(0.0f);
	ParentScene->addChild(FailedSprite, 3);

	auto FadeInAction = FadeIn::create(0.8f);
	FailedSprite->runAction(FadeInAction);
}

void GameSquare::SetActivationFreeze(bool argbActivationFrozen)
{
	bActivationFrozen = argbActivationFrozen;

	if (State == ESquareState::DuringActivation)
	{
		if (bActivationFrozen)
			Director::getInstance()->getActionManager()->pauseTarget(ActivationSprite);
		else
			Director::getInstance()->getActionManager()->resumeTarget(ActivationSprite);
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
