// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "StarImage.h"
#include "GameScene.h"

USING_NS_CC;

#define CURRENT_SPRITE_SIZE 34.0f
#define RECORD_SPRITE_SIZE 46.0f
#define TEXTURES_SIZE 512.0f

const std::string StarImage::StarImageFilePath_Active = "img/squares/square_star_512.png";
const std::string StarImage::StarImageFilePath_Inactive = "img/squares/square_inactive_512.png";


StarImage::StarImage(GameScene* argScene, const Vec2& argPosition, const bool RecordSpriteActive):
ParentScene(argScene),
Position(argPosition)
{
	auto CurrentSprite = Sprite::create(StarImageFilePath_Active);
	CurrentSprite->setPosition(Position);
	CurrentSprite->setScale(CURRENT_SPRITE_SIZE / TEXTURES_SIZE);
	ParentScene->addChild(CurrentSprite, 2);

	auto RecordSprite = RecordSpriteActive ? Sprite::create(StarImageFilePath_Active) : Sprite::create(StarImageFilePath_Inactive);
	RecordSprite->setPosition(Position);
	RecordSprite->setScale(RECORD_SPRITE_SIZE / TEXTURES_SIZE);
	ParentScene->addChild(RecordSprite, 1);
}

void StarImage::Inactivate()
{
	auto FailedSprite = Sprite::create(StarImageFilePath_Inactive);
	FailedSprite->setPosition(Position);
	FailedSprite->setScale(CURRENT_SPRITE_SIZE / TEXTURES_SIZE);
	FailedSprite->setOpacity(0.0f);
	FailedSprite->runAction(FadeIn::create(0.15f));
	ParentScene->addChild(FailedSprite, 3);
}