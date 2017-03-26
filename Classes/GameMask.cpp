// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "GameMask.h"
#include "GameScene.h"

USING_NS_CC;

GameMask::GameMask(GameScene* argScene) :
ParentScene(argScene),
MaskSprite(nullptr)
{
	MaskSprite = Sprite::create("Mask1.png");
	float PosY = Director::getInstance()->getVisibleSize().height * 0.5f;
	MaskSprite->setPosition(ParentScene->GetScreenPositionX(0), PosY);
	MaskSprite->setOpacity(0.0f);
	ParentScene->addChild(MaskSprite, 4);

	auto FadeInAction = FadeIn::create(0.3f);
	auto DelayAction = DelayTime::create(1.0f);
	auto FadeOutAction = FadeOut::create(0.3f);
	auto SequenceAction = Sequence::create(FadeInAction, DelayAction, FadeOutAction, nullptr);

	MaskSprite->runAction(RepeatForever::create(SequenceAction));
}