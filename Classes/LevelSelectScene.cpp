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
		Director::getInstance()->replaceScene(GameScene::create(1, 1.4f, 1.6f, false));
	});
	Level1Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level1Button);

	auto Level2Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(2, 0.9f, 1.4f, false));
	});
	Level2Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level2Button);

	auto Level3Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(3, 0.7f, 1.4f, false));
	});
	Level3Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.7f));
	MenuItems.pushBack(Level3Button);

	auto Level4Button = MenuItemImage::create("Level4_idle.png", "Level4_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(4, 0.5f, 1.4f, false));
	});
	Level4Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.55f));
	MenuItems.pushBack(Level4Button);

	auto Level5Button = MenuItemImage::create("Level5_idle.png", "Level5_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(5, 0.35f, 1.4f, false));
	});
	Level5Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.55f));
	MenuItems.pushBack(Level5Button);

	auto Level6Button = MenuItemImage::create("Level6_idle.png", "Level6_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(6, 0.25f, 1.4f, false));
	});
	Level6Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.55f));
	MenuItems.pushBack(Level6Button);

	auto Level11Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(11, 1.4f, 1.6f, true));
	});
	Level11Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.35f));
	MenuItems.pushBack(Level11Button);

	auto Level12Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(12, 0.9f, 1.4f, true));
	});
	Level12Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.35f));
	MenuItems.pushBack(Level12Button);

	auto Level13Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(13, 0.7f, 1.4f, true));
	});
	Level13Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.35f));
	MenuItems.pushBack(Level13Button);

	auto Level14Button = MenuItemImage::create("Level4_idle.png", "Level4_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(14, 0.5f, 1.4f, true));
	});
	Level14Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.2f));
	MenuItems.pushBack(Level14Button);

	auto Level15Button = MenuItemImage::create("Level5_idle.png", "Level5_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(15, 0.35f, 1.4f, true));
	});
	Level15Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.2f));
	MenuItems.pushBack(Level15Button);

	auto Level16Button = MenuItemImage::create("Level6_idle.png", "Level6_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(16, 0.25f, 1.4f, true));
	});
	Level16Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.2f));
	MenuItems.pushBack(Level16Button);

	auto LevelMenu = Menu::createWithArray(MenuItems);
	LevelMenu->setPosition(Vec2::ZERO);
	this->addChild(LevelMenu, 1);

	return true;
}