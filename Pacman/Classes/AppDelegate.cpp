#include "AppDelegate.h"
#include "View\MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Controller/SoundController.h"
USING_NS_CC;

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Pacman");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
	glview->setDesignResolutionSize(750, 450, kResolutionExactFit);
    //director->setDisplayStats(true); // show fps

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	SoundController* soundController = new SoundController();

    // create a scene. it's an autorelease object
	MainMenuScene* mainMenu = MainMenuScene::create(soundController);
	
    // run
	Director::getInstance()->pushScene(mainMenu->getScene());
    director->runWithScene(mainMenu->getScene());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}