#include "AppDelegate.h"
#include "View/MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Controller/SoundController.h"
USING_NS_CC;

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Pacman");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(750, 450, ResolutionPolicy::EXACT_FIT);
    director->setAnimationInterval(1.0 / 60);

	MainMenuScene* mainMenu = MainMenuScene::create(new SoundController());
	Director::getInstance()->pushScene(mainMenu->getScene());
    director->runWithScene(mainMenu->getScene());

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}