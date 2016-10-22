#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameOver.h"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


void GameOver::BackToMenu(Ref * ref)
{
	Scene * scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(3,scene));
}

// on "init" you need to initialize your instance
bool GameOver::init()
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

	auto Size = Director::getInstance()->getVisibleSize();
	auto Ori = Director::getInstance()->getVisibleOrigin();

	auto menu = Menu::create();
	this->addChild(menu);

	auto Back = MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt", "Back to main menu"), CC_CALLBACK_1(GameOver::BackToMenu, this));
	Back->setPosition(Ori.x -20, Ori.y);
	menu->addChild(Back);

	Label * ScoreLabel = Label::createWithBMFont("futura-48.fnt", "Your final score ");
	ScoreLabel->setColor(Color3B::ORANGE);
	ScoreLabel->setScale(0.8);
	ScoreLabel->setPosition(Ori.x +400, Ori.y + 400);
	this->addChild(ScoreLabel);

	Label * GameOverLabel = Label::createWithBMFont("futura-48.fnt", "Game   Over!");
	GameOverLabel->setColor(Color3B::MAGENTA);
	GameOverLabel->setScale(1.5);
	GameOverLabel->setPosition(Ori.x + 450, Ori.y + 500);
	this->addChild(GameOverLabel);

	return true;
}

void GameOver::onEnter()
{
	Layer::onEnter();
	
	std::string Score0 = score.asString();

	Label * ScoreL = Label::createWithBMFont("futura-48.fnt", Score0);
	ScoreL->setColor(Color3B::ORANGE);
	ScoreL->setScale(0.8);
	ScoreL->setPosition(620, 400);
	this->addChild(ScoreL);	
}

void GameOver::onExit()
{
	Layer::onExit();
}
