#include "Controller\SoundController.h"
#define  DIR "audio/"
#define  EXE ".wav"

static std::vector<std::string> soundNames;
using namespace NSoundController;

void SoundController::init() {
	if(soundNames.empty()) {
		soundNames.push_back(DIR"eatfruit"EXE);//	ES_EAT_FRUIT
		soundNames.push_back(DIR"eatspirit"EXE);//	ES_EAT_SPIRIT,
		soundNames.push_back(DIR"sirensound"EXE);//	ES_SIREN_SOUND,
		soundNames.push_back(DIR"pacman_song2"EXE);//	ES_PACMAN_SOUNG,
		soundNames.push_back(DIR"pacman_coinin"EXE);//	ES_PACMAN_COINING,
	}
}

void SoundController::playMusic(ESounds sound, bool isLoop) {
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundNames.at(sound).c_str(), isLoop);
}

void SoundController::playEffect(ESounds sound, bool isLoop) {
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundNames.at(sound).c_str(), isLoop);
}

void SoundController::preloadingAndPlayMusic(ESounds sound, bool isLoop) {
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(soundNames.at(sound).c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundNames.at(sound).c_str(), isLoop);
}

void SoundController::preloadingAndPlayEffect(ESounds sound, bool isLoop) {
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(soundNames.at(sound).c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundNames.at(sound).c_str(), isLoop);
}

void SoundController::preloadEffect(ESounds sound) {
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(soundNames.at(sound).c_str());
}
