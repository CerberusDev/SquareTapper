// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene) :
ParentScene(argScene),
MaskSprite(nullptr),
StartIndex(0)
{
	MaskSprite = Sprite::create("Mask1.png");
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 4);
	UpdatePosition();

	auto FadeInAction = FadeIn::create(0.3f);
	auto DelayAction = DelayTime::create(2.0f);
	auto FadeOutAction = FadeOut::create(0.3f);
	auto OnFadingOutEndFunction = CallFunc::create([&]() {OnFadingOutEnd(); });
	auto SequenceAction = Sequence::create(FadeInAction, DelayAction, FadeOutAction, OnFadingOutEndFunction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));
}

void GameMask::UpdatePosition()
{
	float PosY = Director::getInstance()->getVisibleSize().height * 0.5f;
	MaskSprite->setPosition(ParentScene->GetScreenPositionX(StartIndex), PosY);
}

void GameMask::OnFadingOutEnd()
{
	StartIndex = (++StartIndex % SQUARE_AMOUNT_X);
	UpdatePosition();
}