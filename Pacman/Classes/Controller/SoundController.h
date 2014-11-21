#ifndef SOUND_CONTROLLER_H_
#define SOUND_CONTROLLER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


enum ESounds {
	ES_EAT_FRUIT = 0,
	ES_EAT_SPIRIT,
	ES_SIREN_SOUND,
	ES_PACMAN_SOUNG,
	ES_PACMAN_COINING,

	ES_LAST
};

class SoundController {
public:
	void preloadEffect(ESounds sound);
	void playMusic(ESounds sound, bool isLoop = false);
	void preloadingAndPlayMusic(ESounds sound, bool isLoop = false);
	void preloadingAndPlayEffect(ESounds sound, bool isLoop = false);
	void playEffect(ESounds sound, bool isLoop = false);
};

#endif /* SOUND_CONTROLLER_H_ */
