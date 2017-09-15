// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

#define SPRITE_SIZE 160.0f
#define FAILED_SPRITE_SIZE 46.0f
#define TEXTURES_SIZE 512.0f

const std::string GameSquare::ActivationSpriteFilename_Safe = "gui/squares/square_safe_main_512.png";
const std::string GameSquare::ActivationSpriteFilename_Standard = "gui/squares/square_active_512.png";
const std::string GameSquare::ActivationSpriteFilename_Dangerous = "gui/squares/square_dangerous_main_512.png";
const std::string GameSquare::ActivationSpriteFilename_DangerousSecondTap = "gui/squares/square_active_512.png";

GameSquare::GameSquare(Scene* argScene, const bool bargDoubleTap, ESquareSafetyType argSafetyType, const Vec2& argSpritePosition, int argPosX, int argPosY, const std::string& InactiveSpriteFilename):
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
SafetyType(argSafetyType),
SavedActivationTotalTime(-1.0f),
CompletedSpriteFadeInTime(0.15f),
SpritesScale(SPRITE_SIZE / TEXTURES_SIZE),
ActivationFreezeRequestsCounter(0),
bDoubleTap(bargDoubleTap),
bAlreadyTapped(false),
bBlockTouchEvents(false),
bPausedOnGameOver(false)
{
	InactiveSprite = Sprite::create(InactiveSpriteFilename);
	InactiveSprite->setPosition(SpritePosition);
	InactiveSprite->setScale(SpritesScale);
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

	ActivationSprite = Sprite::create(GetActivationSpriteFilename(SafetyType));
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

	auto ScaleAction = ScaleTo::create(ActivationTotalTime, SpritesScale);
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
	if (SafetyType == ESquareSafetyType::Dangerous || (SafetyType == ESquareSafetyType::DangerousSecondTap && bDoubleTap && bAlreadyTapped))
	{
		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);
		auto ScaleSequence = ScaleUpActivationSquare();
		Failed(ScaleSequence);
	}
	else if (bDoubleTap && !bAlreadyTapped)
	{
		if (SafetyType == ESquareSafetyType::DangerousSecondTap)
			ActivationSprite->setTexture(GetActivationSpriteFilename(ESquareSafetyType::Dangerous));

		InactiveSprite->setTexture("gui/bqsqr/bgsqr_0_inactive_512.png");
		bAlreadyTapped = true;

		SetActivationFreeze(true);

		auto DelayAction = DelayTime::create(0.23f);
		auto UnfreezeFunc = CallFunc::create([&]() {
			SetActivationFreeze(false);
		});

		InactiveSprite->runAction(Sequence::create(DelayAction, UnfreezeFunc, nullptr));
	}
	else
	{
		State = ESquareState::Completed;

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(ActivationSprite);

		auto ScaleSequence = ScaleUpActivationSquare();
		ShowFinalSprites(false, ScaleSequence);

		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->OnSquareCompleted(this);
	}
}

void GameSquare::ActivationEnded()
{
	if (SafetyType != ESquareSafetyType::Standard)
	{
		State = ESquareState::Completed;

		ShowFinalSprites(false);

		if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
			ParentGameScene->OnSquareCompleted(this);
	}
	else
	{
		Failed();
	}
}

void GameSquare::Failed(cocos2d::Sequence* ScaleUpSequence)
{
	State = ESquareState::Failed;

	ShowFinalSprites(true, ScaleUpSequence);

	if (GameScene* ParentGameScene = dynamic_cast<GameScene*>(ParentScene))
		ParentGameScene->OnSquareFailed(this);
}

void GameSquare::ShowFinalSprites(bool bShowFailedSprite, cocos2d::Sequence* ScaleUpSequence)
{
	CompletedSprite = Sprite::create("gui/squares/square_inactive_512.png");
	CompletedSprite->setPosition(SpritePosition);
	CompletedSprite->setOpacity(0.0f);
	CompletedSprite->setScale(ActivationSprite->getScale());
	ParentScene->addChild(CompletedSprite, 3);

	auto FadeInAction = FadeIn::create(CompletedSpriteFadeInTime);

	if (ScaleUpSequence)
		CompletedSprite->runAction(Spawn::createWithTwoActions(FadeInAction, ScaleUpSequence->clone()));
	else
		CompletedSprite->runAction(FadeInAction);

	if (bShowFailedSprite)
	{
		FailedSprite = Sprite::create("gui/squares/square_star_512.png");
		FailedSprite->setPosition(SpritePosition);
		FailedSprite->setScale(FAILED_SPRITE_SIZE / TEXTURES_SIZE);
		FailedSprite->setOpacity(0.0f);
		ParentScene->addChild(FailedSprite, 3);

		auto FadeInAction = FadeIn::create(CompletedSpriteFadeInTime);
		FailedSprite->runAction(FadeInAction);
	}
}

Sequence* GameSquare::ScaleUpActivationSquare()
{
	auto ScaleAction1 = ScaleTo::create(0.04f, SpritesScale);
	auto ScaleAction2 = ScaleTo::create(0.04f, SpritesScale * 1.07f);
	auto ScaleAction3 = ScaleTo::create(0.07f, SpritesScale);
	auto ScaleSequence = Sequence::create(ScaleAction1, ScaleAction2, ScaleAction3, nullptr);
	ActivationSprite->runAction(ScaleSequence);

	return ScaleSequence;
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

const std::string& GameSquare::GetActivationSpriteFilename(ESquareSafetyType argSafetyType)
{
	switch (argSafetyType)
	{
	case ESquareSafetyType::Safe:				return ActivationSpriteFilename_Safe;
	case ESquareSafetyType::Standard:			return ActivationSpriteFilename_Standard;
	case ESquareSafetyType::Dangerous:			return ActivationSpriteFilename_Dangerous;
	case ESquareSafetyType::DangerousSecondTap:	return ActivationSpriteFilename_DangerousSecondTap;
	}
}
