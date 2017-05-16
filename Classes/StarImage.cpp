// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "StarImage.h"
#include "GameScene.h"

USING_NS_CC;

StarImage::StarImage(GameScene* ParentScene, const Vec2& Position)
{
	ActiveSprite = Sprite::create("img/ui/Star_active.png");
	ActiveSprite->setPosition(Position);
	ParentScene->addChild(ActiveSprite, 2);

	InactiveSprite = Sprite::create("img/ui/Star_inactive.png");
	InactiveSprite->setPosition(Position);
	ParentScene->addChild(InactiveSprite, 1);
}

void StarImage::Inactivate()
{
	ActiveSprite->runAction(ScaleTo::create(0.4f, 0.0f));
}