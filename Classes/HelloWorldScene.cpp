#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MySquare.h"
#include "LevelSelectScene.h"

USING_NS_CC;

bool HelloWorld::init()
{
    if (!Scene::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<MenuItem*> MenuItems;

    auto BackItem = MenuItemImage::create("Back_idle.png", "Back_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(LevelSelectScene::create());
	});
    
	BackItem->setPosition(Vec2(origin.x + visibleSize.width * 0.77f, origin.y + visibleSize.height * 0.07f));
	MenuItems.pushBack(BackItem);

	auto RestartItem = MenuItemImage::create("Restart_idle.png", "Restart_pressed.png",
		[&](Ref* sender) {
		Director::getInstance()->replaceScene(HelloWorld::create());
	});

	RestartItem->setPosition(Vec2(origin.x + visibleSize.width * 0.88f, origin.y + visibleSize.height * 0.07f));
	MenuItems.pushBack(RestartItem);

    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	float FontSize = 50.0f / Director::getInstance()->getContentScaleFactor();
    auto label = Label::createWithTTF("Tap the squares!", "fonts/Marker Felt.ttf", FontSize);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2.0f,
                            origin.y + visibleSize.height * 0.975f - label->getContentSize().height));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);

	float OffsetX = 0.23f;
	float OffsetY = 0.2f;

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
	{
		float PosXMod = OffsetX + (float)x / (SQUARE_AMOUNT_X - 1) * (1.0f - 2.0f * OffsetX);

		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
		{
			float PosYMod = OffsetY + (float)y / (SQUARE_AMOUNT_Y - 1) * (1.0f - 2.0f * OffsetY);
			Vec2 Pos = Vec2(visibleSize.width * PosXMod + origin.x, visibleSize.height * PosYMod + origin.y);
			Squares[x][y] = new MySquare(this, Pos);
			AvailableSquares.push_back(std::pair<int, int>(x, y));
		}
	}

	std::random_shuffle(AvailableSquares.begin(), AvailableSquares.end());

	auto StartDelayAction = DelayTime::create(0.5f);
	auto StartShowing = CallFunc::create([&]() {
		ShowNextSquare();
	});
	runAction(Sequence::create(StartDelayAction, StartShowing, nullptr));

	CCLOG("Initialization end");

    return true;
}

void HelloWorld::onExit()
{
	Scene::onExit();

	for (int x = 0; x < SQUARE_AMOUNT_X; ++x)
		for (int y = 0; y < SQUARE_AMOUNT_Y; ++y)
			delete Squares[x][y];
}

void HelloWorld::ShowNextSquare()
{
	if (!AvailableSquares.empty())
	{
		auto DelayAction = DelayTime::create(0.3f);
		auto StartFunc = CallFunc::create([&]() {
			std::pair<int, int> NextSquareCoords = AvailableSquares.back();
			Squares[NextSquareCoords.first][NextSquareCoords.second]->StartShowing();
			AvailableSquares.pop_back();
		});

		runAction(Sequence::create(DelayAction, StartFunc, nullptr));
	}
}
