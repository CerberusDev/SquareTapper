// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "GameSquare.h"

USING_NS_CC;

GameSquare::GameSquare(GameScene* argScene, const Vec2& argSpritePosition, int argPosX, int argPosY):
PosX(argPosX), PosY(argPosY), ParentScene(argScene), MySprite(nullptr), MySecondSprite(nullptr), 
SpritePosition(argSpritePosition), State(ESquareState::Inactive), bCoveredByMask(false)
{
	MySprite = Sprite::create("Square1.png");
	MySprite->setPosition(SpritePosition);
	ParentScene->addChild(MySprite, 1);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [&](Touch* touch, Event* event) {
		Vec2 p = touch->getLocation();
		Rect rect = MySprite->getBoundingBox();

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

	//listener1->onTouchEnded = [=](Touch* touch, Event* event) {
	//	OnTouch(touch, event);
	//};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, ParentScene);

	MySecondSprite = Sprite::create("Square2.png");
	MySecondSprite->setPosition(SpritePosition);
	MySecondSprite->setScale(0.0f);
	ParentScene->addChild(MySecondSprite, 2);
}

void GameSquare::StartActivation(float ActivationTotalTime)
{
	State = ESquareState::DuringActivation;

	auto ScaleAction = ScaleTo::create(ActivationTotalTime, 1.0f);
	auto EndFunc = CallFunc::create([&]() {
		State = ESquareState::Failed;
		ParentScene->OnSquareFailed();
	});
	MySecondSprite->runAction(Sequence::create(ScaleAction, EndFunc, nullptr));
}

void GameSquare::OnTouch(Touch* touch, Event* event)
{
	CCLOG("Touched! %f %f", touch->getLocation().x, touch->getLocation().y);

	if (State == ESquareState::DuringActivation)
	{
		State = ESquareState::Completed;

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(MySecondSprite);

		auto ScaleAction1 = ScaleTo::create(0.075f, 1.0f);
		auto ScaleAction2 = ScaleTo::create(0.075f, 1.1f);
		auto ScaleAction3 = ScaleTo::create(0.15f, 1.0f);
		MySecondSprite->runAction(Sequence::create(ScaleAction1, ScaleAction2, ScaleAction3, nullptr));

		ParentScene->OnSquareCompleted();
	}
}

void GameSquare::SetCoveredByMask(bool argbCoveredByMask)
{
	bCoveredByMask = argbCoveredByMask;

	if (bCoveredByMask)
		Director::getInstance()->getActionManager()->pauseTarget(MySecondSprite);
	else
		Director::getInstance()->getActionManager()->resumeTarget(MySecondSprite);
}
