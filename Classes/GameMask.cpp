// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene, std::string SpriteFilePath, std::string argBlinkSpriteFilePath, bool bKillingMask) :
ParentScene(argScene),
MaskSprite(nullptr),
BlinkSpriteFilePath(argBlinkSpriteFilePath),
bKillOnTouch(bKillingMask),
bMaskFullyVisible(false),
bShouldFinishAnimation(false)
{
	MaskSprite = Sprite::create(SpriteFilePath);
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 3);

	auto FadeInAction = FadeIn::create(0.15f);
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

		Sprite* BlinkSprite = Sprite::create(BlinkSpriteFilePath);
		BlinkSprite->setPosition(MaskSprite->getPosition());
		BlinkSprite->setOpacity(0.0f);
		ParentScene->addChild(BlinkSprite, 4);

		auto FadeInAction = FadeIn::create(0.07f);
		auto FadeOutAction = FadeOut::create(0.15f);
		BlinkSprite->runAction(Sequence::create(FadeInAction, FadeOutAction, nullptr));
	}
}
