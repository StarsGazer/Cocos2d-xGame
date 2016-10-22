#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Instruction.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Instruction::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Instruction::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Instruction::BackToMenu(Ref *ref)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(3, scene));
}

// on "init" you need to initialize your instance
bool Instruction::init()
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
	Vec2 Ori = Director::getInstance()->getVisibleOrigin();

	auto menu = Menu::create();
	this->addChild(menu);
	auto Back = MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt", "Back to main menu"), CC_CALLBACK_1(Instruction::BackToMenu, this));
	Back->setPosition(Ori.x-50,Ori.y-200);
	Back->setScale(1);
	Back->setColor(Color3B::GRAY);
	menu->addChild(Back);

	auto Ins1 = Label::createWithBMFont("futura-48.fnt", "How to play");//说明标题
	Ins1->setPosition(Ori.x +450 , Ori.y +550);
	Ins1->setColor(Color3B::MAGENTA);
	this->addChild(Ins1);

	auto Ins2 = Label::createWithBMFont("futura-48.fnt", "Your Tank");
	Ins2->setPosition(Ori.x + 420, Ori.y + 450);
	Ins2->setColor(Color3B::ORANGE);
	Ins2->setScale(0.7);
	this->addChild(Ins2);

	auto Ins3 = Label::createWithBMFont("futura-48.fnt", "EnemyTank");
	Ins3->setPosition(Ori.x + 420, Ori.y + 380);
	Ins3->setColor(Color3B::ORANGE);
	Ins3->setScale(0.7);
	this->addChild(Ins3);

	auto Ins4 = Label::createWithBMFont("futura-48.fnt", "Press W  A  S  D to move");
	auto Ins5 = Label::createWithBMFont("futura-48.fnt", "Press J to shoot");
	auto Ins6 = Label::createWithBMFont("futura-48.fnt", "Press P to pause");

	Ins4->setPosition(Ori.x + 450,Ori.y+320);
	Ins4->setColor(Color3B::ORANGE);
	Ins4->setScale(0.7);
	this->addChild(Ins4);
	Ins5->setPosition(Ori.x + 450, Ori.y + 260);
	Ins5->setColor(Color3B::ORANGE);
	Ins5->setScale(0.7);
	this->addChild(Ins5);
	Ins6->setPosition(Ori.x + 450, Ori.y + 200);
	Ins6->setColor(Color3B::ORANGE);
	Ins6->setScale(0.7);
	this->addChild(Ins6);

	auto InsMyTank = Sprite::create("tank.png");
	InsMyTank->setPosition(Ori.x + 550, Ori.y + 450);
	InsMyTank->setScale(3);
	this->addChild(InsMyTank);

	auto InsEnemy = Sprite::create("enemyTank.png");
	InsEnemy->setPosition(Ori.x + 550, Ori.y + 380);
	InsEnemy->setScale(3);
	this->addChild(InsEnemy);

	return true;
}
