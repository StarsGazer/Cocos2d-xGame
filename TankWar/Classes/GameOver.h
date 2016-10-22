#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

class GameOver : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

	void BackToMenu(Ref *ref);

	Value score;//GameOver场景下的分数

	virtual void onEnter();
	virtual void onExit();

private:
	
};

#endif // __HELLOWORLD_SCENE_H__