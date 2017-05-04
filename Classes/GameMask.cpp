// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene, std::string SpriteFilePath, bool bKillingMask) :
ParentScene(argScene),
MaskSprite(nullptr),
bKillOnTouch(bKillingMask)
{
	MaskSprite = Sprite::create(SpriteFilePath);
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 3);

	auto FadeInAction = FadeIn::create(0.15f);
	auto OnFadingInEndFunction = CallFunc::create([&]() { CoverSquares(); });
	auto DelayAction = DelayTime::create(0.6f);
	auto OnFadingOutStartFunction = CallFunc::create([&]() { UncoverSquares(); });
	auto FadeOutAction = FadeOut::create(0.15f);
	auto OnFadingOutEndFunction = CallFunc::create([&]() { OnFadingOutEnd(); });
	auto SequenceAction = Sequence::create(FadeInAction, OnFadingInEndFunction, DelayAction, OnFadingOutStartFunction, FadeOutAction, OnFadingOutEndFunction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));

	if (bKillOnTouch)
	{
		EventListener = EventListenerTouchOneByOne::create();
		EventListener->setSwallowTouches(true);
		EventListener->onTouchBegan = [&](Touch* touch, Event* event) {
			if (MaskSprite->getBoundingBox().containsPoint(touch->getLocation()))
			{
				OnTouch(touch, event);
				return true;
			}
			else
			{
				return false;
			}
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(EventListener, 1);
	}
}

GameMask::~GameMask()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(EventListener);
}

void GameMask::OnGameOver()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(MaskSprite);
}

void GameMask::UncoverSquares()
{
	for (auto CurrSquare : CoveredSquares)
		CurrSquare->SetCoveredByMask(false);

	CoveredSquares.clear();
}

void GameMask::OnFadingOutEnd()
{
	Move();
	UpdateSpritePosition();
}

void GameMask::OnTouch(Touch* touch, Event* event)
{
	ParentScene->LevelFailed();
}
