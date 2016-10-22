#ifndef __GAMESCENE2_H__
#define __GAMESCENE2_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene2 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

private:
	virtual bool init();

	// implement the "static create()" method manually
public:
	CREATE_FUNC(GameScene2);
	void GameOn(Ref *ref);


private:

};

#endif // __HELLOWORLD_SCENE_H__
