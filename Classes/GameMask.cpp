// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

#define MAX_OPACITY 255

const std::string GameMask::StandardMaskSpriteFilename = "gui/squares/square_safe_main_512.png";
const std::string GameMask::KillingMaskSpriteFilename = "gui/squares/square_dangerous_main_512.png";

GameMask::GameMask(GameScene* argScene, bool bKillingMask) :
ParentScene(argScene),
MaskSprite(nullptr),
bKillOnTouch(bKillingMask),
bMaskFullyVisible(false),
bShouldFinishAnimation(false)
{
	MaskSprite = Sprite::create(bKillOnTouch ? KillingMaskSpriteFilename : StandardMaskSpriteFilename);
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 0);

	auto FadeInAction = FadeTo::create(0.15f, MAX_OPACITY);
	auto OnFadingInEndFunction = CallFunc::create([&]() { OnFadingInEnd(); });
	auto DelayAction = DelayTime::create(0.6f);
	auto OnFadingOutStartFunction = CallFunc::create([&]() { OnFadingOutStart(); });
	auto FadeOutAction = FadeOut::create(0.15f);
	auto OnFadingOutEndFunction = CallFunc::create([&]() { OnFadingOutEnd(); });
	auto SequenceAction = Sequence::create(FadeInAction, OnFadingInEndFunction, DelayAction, OnFadingOutStartFunction, FadeOutAction, OnFadingOutEndFunction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));

	if (bKillOnTouch)
	{
		EventListener = EventListenerTouchOneByOne::create();
		EventListener->onTouchBegan = [&](Touch* touch, Event* event) {
			if (MaskSprite->getBoundingBox().containsPoint(touch->getLocation()))
				OnTouch(touch, event);

			return false;
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(EventListener, 1);
	}
}

GameMask::~GameMask()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(EventListener);
}

void GameMask::FinishAnimation()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(MaskSprite);
}

void GameMask::UnfrozeSquareActivation()
{
	for (auto CurrSquare : FrozenSquares)
		CurrSquare->SetActivationFreeze(false);

	FrozenSquares.clear();
}

void GameMask::OnFadingInEnd()
{
	for (auto CurrSquare : FrozenSquares)
		CurrSquare->SetBlockTouchEvents(true);

	bMaskFullyVisible = true;

	if (bShouldFinishAnimation)
		FinishAnimation();
}

void GameMask::OnFadingOutStart()
{
	for (auto CurrSquare : FrozenSquares)
		CurrSquare->SetBlockTouchEvents(false);

	bMaskFullyVisible = false;

	if (bShouldFinishAnimation)
		FinishAnimation();
}

void GameMask::OnFadingOutEnd()
{
	UnfrozeSquareActivation();
	Move();
	UpdateSpritePosition();
	FrozeSquareActivation();
}

void GameMask::OnTouch(Touch* touch, Event* event)
{
	if (bMaskFullyVisible && !ParentScene->IsLevelFinished())
	{
		ParentScene->DecreaseStarNumber();

		// Blinking temporary disabled
		//Sprite* BlinkSprite = Sprite::create(BlinkSpriteFilePath);
		//BlinkSprite->setPosition(MaskSprite->getPosition());
		//BlinkSprite->setOpacity(0.0f);
		//ParentScene->addChild(BlinkSprite, 6);

		//auto FadeInAction = FadeIn::create(0.07f);
		//auto FadeOutAction = FadeOut::create(0.15f);
		//BlinkSprite->runAction(Sequence::create(FadeInAction, FadeOutAction, nullptr));
	}
}
