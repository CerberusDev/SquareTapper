// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "BaseScene.h"

USING_NS_CC;

void BaseScene::Blink(bool bLongWhiteBlink)
{
	auto BlinkSprite = Sprite::create(bLongWhiteBlink ? "gui/squares/square_active_512.png" : "gui/squares/square_star_512.png");
	BlinkSprite->setOpacity(0.0f);
	BlinkSprite->setPosition(DESIGN_RES_X / 2.0f, DESIGN_RES_Y / 2.0f);
	BlinkSprite->setScale(DESIGN_RES_X / SQUARE_TEXTURES_SIZE, DESIGN_RES_Y / SQUARE_TEXTURES_SIZE);

	if (bLongWhiteBlink)
	{
		addChild(BlinkSprite, 0);

		auto FadeInAction = FadeTo::create(0.10f, 255);
		auto DelayAction = DelayTime::create(0.16f);
		auto FadeOutAction = FadeTo::create(0.25f, 0);
		auto RemoveMyself = CallFunc::create([BlinkSprite]() {
			BlinkSprite->removeFromParent();
		});

		BlinkSprite->runAction(Sequence::create(FadeInAction, DelayAction, FadeOutAction, RemoveMyself, nullptr));
	}
	else
	{
		addChild(BlinkSprite, 30);

		auto FadeInAction = FadeTo::create(0.07f, 160);
		auto FadeOutAction = FadeTo::create(0.3f, 0);
		auto RemoveMyself = CallFunc::create([BlinkSprite]() {
			BlinkSprite->removeFromParent();
		});

		BlinkSprite->runAction(Sequence::create(FadeInAction, FadeOutAction, RemoveMyself, nullptr));
	}
}
