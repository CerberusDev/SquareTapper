#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MySquare.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("Restart_idle.png",
                                           "Restart_pressed.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width * 0.815f - closeItem->getContentSize().width / 2.0f,
                                origin.y + visibleSize.height * 0.05f + closeItem->getContentSize().height / 2.0f));

    auto menu = Menu::create(closeItem, nullptr);
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
	Layer::onExit();

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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());

//    Director::getInstance()->end();
//
//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
