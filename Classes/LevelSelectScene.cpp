// ---------------------------------------------------------------------------------------------------
// -------------------------------- SquareTapper by Maciej Pryc, 2017 --------------------------------
// ---------------------------------------------------------------------------------------------------

#include "LevelSelectScene.h"
#include "GameScene.h"

USING_NS_CC;

bool LevelSelectScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	auto label = Label::createWithTTF("Choose level", "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.9f));
	this->addChild(label, 1);

	Vector<MenuItem*> MenuItems;

	auto Level1Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
	[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(1, 1.5f, 1.6f));
	});
	Level1Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level1Button);

	auto Level2Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(2, 1.1f, 1.4f));
	});
	Level2Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level2Button);

	auto Level3Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(3, 0.8f, 1.2f));
	});
	Level3Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level3Button);

	auto Level4Button = MenuItemImage::create("Level4_idle.png", "Level4_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(4, 0.5f, 1.2f));
	});
	Level4Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.55f));
	MenuItems.pushBack(Level4Button);

	auto Level5Button = MenuItemImage::create("Level5_idle.png", "Level5_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(5, 0.3f, 1.2f));
	});
	Level5Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.55f));
	MenuItems.pushBack(Level5Button);

	auto LevelMenu = Menu::createWithArray(MenuItems);
	LevelMenu->setPosition(Vec2::ZERO);
	this->addChild(LevelMenu, 1);

	return true;
}