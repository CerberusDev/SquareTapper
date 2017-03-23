// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameScene.h"
#include "MySquare.h"

USING_NS_CC;

MySquare::MySquare(GameScene* argScene, const Vec2& argPosition):
ParentScene(argScene), MySprite(nullptr), MySecondSprite(nullptr), Position(argPosition), bClickable(false)
{
	MySprite = Sprite::create("Square1.png");
	MySprite->setPosition(Position);
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
	MySecondSprite->setPosition(Position);
	MySecondSprite->setScale(0.0f);
	ParentScene->addChild(MySecondSprite, 2);
}

void MySquare::StartShowing()
{
	bClickable = true;

	auto StartFunc = CallFunc::create([&]() {
		bClickable = true;
	});
	auto ScaleAction = ScaleTo::create(1.5f, 1.0f);
	auto EndFunc = CallFunc::create([&]() {
		bClickable = false;
		ParentScene->ShowNextSquare();
	});
	MySecondSprite->runAction(Sequence::create(StartFunc, ScaleAction, EndFunc, nullptr));
}

void MySquare::OnTouch(Touch* touch, Event* event)
{
	CCLOG("Touched! %f %f", touch->getLocation().x, touch->getLocation().y);

	if (bClickable)
	{
		bClickable = false;

		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(MySecondSprite);

		auto ScaleAction1 = ScaleTo::create(0.075f, 1.0f);
		auto ScaleAction2 = ScaleTo::create(0.075f, 1.1f);
		auto ScaleAction3 = ScaleTo::create(0.15f, 1.0f);
		MySecondSprite->runAction(Sequence::create(ScaleAction1, ScaleAction2, ScaleAction3, nullptr));

		ParentScene->ShowNextSquare();
	}
}
