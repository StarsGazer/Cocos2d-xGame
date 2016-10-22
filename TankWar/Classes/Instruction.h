#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "cocos2d.h"

using namespace cocos2d;

class Instruction: public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Instruction);

	void BackToMenu(Ref *ref);

private:
};

#endif // __HELLOWORLD_SCENE_H__
