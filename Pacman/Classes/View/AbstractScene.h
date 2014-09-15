#ifndef __ABSTRACT_SCENE_H__
#define __ABSTRACT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class AbstractScene : public Layer {

protected:
	Scene* scene_;

public:
	Scene* getScene() const;

};

#endif // __ABSTRACT_SCENE_H__
