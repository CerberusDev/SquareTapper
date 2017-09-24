// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "StarImage.h"
#include "GameScene.h"

USING_NS_CC;

const std::string StarImage::StarImageFilePath_Active = "gui/squares/square_star_512.png";
const std::string StarImage::StarImageFilePath_Inactive = "gui/squares/square_inactive_512.png";


StarImage::StarImage(GameScene* argScene, const Vec2& argPosition, const bool RecordSpriteActive):
ParentScene(argScene),
Position(argPosition)
{
	auto CurrentSprite = Sprite::create(StarImageFilePath_Active);
	CurrentSprite->setPosition(Position);
	CurrentSprite->setScale(STAR_SQUARE_SIZE / SQUARE_TEXTURES_SIZE);
	ParentScene->addChild(CurrentSprite, 2);

	auto RecordSprite = RecordSpriteActive ? Sprite::create(StarImageFilePath_Active) : Sprite::create(StarImageFilePath_Inactive);
	RecordSprite->setPosition(Position);
	RecordSprite->setScale(RECORD_SQUARE_SIZE / SQUARE_TEXTURES_SIZE);
	ParentScene->addChild(RecordSprite, 1);
}

void StarImage::Inactivate()
{
	auto FailedSprite = Sprite::create(StarImageFilePath_Inactive);
	FailedSprite->setPosition(Position);
	FailedSprite->setScale(STAR_SQUARE_SIZE / SQUARE_TEXTURES_SIZE);
	FailedSprite->setOpacity(0.0f);
	FailedSprite->runAction(FadeIn::create(0.15f));
	ParentScene->addChild(FailedSprite, 3);
}