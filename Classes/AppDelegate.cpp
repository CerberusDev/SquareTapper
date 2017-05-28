#include "AppDelegate.h"
#include "LevelSelectScene.h"

USING_NS_CC;

static cocos2d::Size desktopResolutionSize = cocos2d::Size(432, 768);
static cocos2d::Size mobileResolutionSize = cocos2d::Size(720, 1280);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) 
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CocosTest3", cocos2d::Rect(0, 0, desktopResolutionSize.width, desktopResolutionSize.height));
#else
        glview = GLViewImpl::create("CocosTest3");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	glview->setDesignResolutionSize(desktopResolutionSize.width, desktopResolutionSize.height, ResolutionPolicy::NO_BORDER);
	director->setContentScaleFactor(mobileResolutionSize.width / desktopResolutionSize.width);
#else
    glview->setDesignResolutionSize(mobileResolutionSize.width, mobileResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

    register_all_packages();

	director->runWithScene(LevelSelectScene::create(0));

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
