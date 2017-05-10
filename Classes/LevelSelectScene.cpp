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

	std::string FileName = "_Levels.txt";
	std::string FilePath = FileUtils::getInstance()->fullPathForFilename(FileName);
	std::string FileContents = FileUtils::getInstance()->getStringFromFile(FilePath);
	std::istringstream InputStream(FileContents);

	for (std::string Line; std::getline(InputStream, Line); )
	{
		if (Line.size() > 1 && Line[0] != '#')
		{
			LevelParams NewLevelParams;

			std::stringstream(Line) >> NewLevelParams.LevelNumber;
			std::getline(InputStream, Line);
			std::stringstream(Line) >> NewLevelParams.SquaresActivationTimeInterval;
			std::getline(InputStream, Line);
			std::stringstream(Line) >> NewLevelParams.TotalSquareActivationTime;
			std::getline(InputStream, Line);

			if (Line.find("Spawn mask") != std::string::npos)
			{
				NewLevelParams.bSpawnGameMask = true;
				std::getline(InputStream, Line);

				if (Line.find("Vertical") != std::string::npos)
					NewLevelParams.bVerticalMask = true;

				std::getline(InputStream, Line);

				if (Line.find("Killing") != std::string::npos)
					NewLevelParams.bKillingMask = true;
			}

			LevelParamsContainer.push_back(NewLevelParams);
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
	auto label = Label::createWithTTF("Choose level", "fonts/Marker Felt.ttf", FontSize);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.9f));
	this->addChild(label, 1);

	Vector<MenuItem*> MenuItems;

	auto Level1Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
	[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(1, 0.5f, 1.4f, false));
	});
	Level1Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.75f));
	MenuItems.pushBack(Level1Button);

	auto Level2Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(2, 0.35f, 1.4f, false));
	});
	Level2Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.75f));
	MenuItems.pushBack(Level2Button);

	auto Level3Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(3, 0.25f, 1.4f, false));
	});
	Level3Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.75f));
	MenuItems.pushBack(Level3Button);

	// ---------------------------------------------------------------------------------------------------

	auto Level4Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(4, 0.55f, 1.4f, true, false, false));
	});
	Level4Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.6f));
	MenuItems.pushBack(Level4Button);

	auto Level5Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(5, 0.45f, 1.4f, true, false, false));
	});
	Level5Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.6f));
	MenuItems.pushBack(Level5Button);

	auto Level6Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(6, 0.35f, 1.4f, true, false, false));
	});
	Level6Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.6f));
	MenuItems.pushBack(Level6Button);

	// ---------------------------------------------------------------------------------------------------

	auto Level7Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(7, 0.55f, 1.4f, true, true, false));
	});
	Level7Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.45f));
	MenuItems.pushBack(Level7Button);

	auto Level8Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(8, 0.45f, 1.4f, true, true, false));
	});
	Level8Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.45f));
	MenuItems.pushBack(Level8Button);

	auto Level9Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(9, 0.35f, 1.4f, true, true, false));
	});
	Level9Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.45f));
	MenuItems.pushBack(Level9Button);

	// ---------------------------------------------------------------------------------------------------

	auto Level10Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(10, 0.7f, 1.4f, true, false, true));
	});
	Level10Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.3f));
	MenuItems.pushBack(Level10Button);

	auto Level11Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(11, 0.6f, 1.4f, true, false, true));
	});
	Level11Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.3f));
	MenuItems.pushBack(Level11Button);

	auto Level12Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(12, 0.5f, 1.4f, true, false, true));
	});
	Level12Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.3f));
	MenuItems.pushBack(Level12Button);

	// ---------------------------------------------------------------------------------------------------

	auto Level13Button = MenuItemImage::create("Level1_idle.png", "Level1_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(13, 0.7f, 1.4f, true, true, true));
	});
	Level13Button->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.15f));
	MenuItems.pushBack(Level13Button);

	auto Level14Button = MenuItemImage::create("Level2_idle.png", "Level2_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(14, 0.6f, 1.4f, true, true, true));
	});
	Level14Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.15f));
	MenuItems.pushBack(Level14Button);

	auto Level15Button = MenuItemImage::create("Level3_idle.png", "Level3_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::create(15, 0.5f, 1.4f, true, true, true));
	});
	Level15Button->setPosition(Vec2(origin.x + visibleSize.width * 0.75f, origin.y + visibleSize.height * 0.15f));
	MenuItems.pushBack(Level15Button);

	auto LevelMenu = Menu::createWithArray(MenuItems);
	LevelMenu->setPosition(Vec2::ZERO);
	this->addChild(LevelMenu, 1);

	return true;
}