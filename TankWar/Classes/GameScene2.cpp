#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene2.h"
#include "GameOver.h"
#include <vector>
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace std;
using namespace cocostudio::timeline;
USING_NS_CC;

void GameScene2::GameOn(Ref *ref)
{
	Scene * GScene = GameScene::createScene();//创建游戏界面的场景
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, GScene));
}

Scene* GameScene2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}



// on "init" you need to initialize your instance
bool GameScene2::init()
{
	/**  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if ( !Layer::init() )
	{
	return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	**/

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	

	Size vsize = Director::getInstance()->getVisibleSize();
	Vec2 Mid = Director::getInstance()->getVisibleOrigin();


	auto menu = Menu::create();
	this->addChild(menu);

	auto Continue = Label::createWithBMFont("futura-48.fnt", "You have passed the stage!");
	Continue->setColor(Color3B::MAGENTA);
	Continue->setPosition(450, 500);
	Continue->setScale(1.2);
	this->addChild(Continue);

	auto StartMenu = MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt", "Press here to continue"), CC_CALLBACK_1(GameScene2::GameOn, this));
	StartMenu->setPosition(Mid.x, Mid.y);
	StartMenu->setColor(Color3B::ORANGE);

	menu->addChild(StartMenu);



	return true;
}

