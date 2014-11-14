#include "Controller\SoundController.h"

void SoundController::init() {
	if(soundNames.empty()) {
		soundNames.push_back("audio/eatfruit.wav");//	ES_EAT_FRUIT
		soundNames.push_back("audio/eatspirit.wav");//	ES_EAT_SPIRIT,
		soundNames.push_back("audio/sirensound.wav");//	ES_SIREN_SOUND,
		soundNames.push_back("audio/pacman_song2.wav");//	ES_PACMAN_SOUNG,
		soundNames.push_back("audio/pacman_coinin.wav");//	ES_PACMAN_COINING,
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
