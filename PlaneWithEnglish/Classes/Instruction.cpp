#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "Instruction.h"
#include "ui/CocosGUI.h"

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

std::string WStrToUTF8a(const std::wstring& src)//���������������
{
	std::string dest;
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
		{
			dest.push_back((char)w);
		}
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
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


	return true;
}

void Instruction::BackToMenu(Ref *ref)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void Instruction::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	auto Title = Label::create(WStrToUTF8a(L"��Ϸ˵��"), "��Բ", 36);
	Title->setColor(Color3B::YELLOW);
	Title->setPosition(480, 520);
	this->addChild(Title);

	auto Content1 = Label::create(WStrToUTF8a(L"��Ϸ��,��W,A,S,D���Ʒɻ��ƶ�,J���Ʒɻ����."),"��Բ",28);
	Content1->setColor(Color3B::ORANGE);
	Content1->setPosition(440, 460);
	this->addChild(Content1);

	auto Content2 = Label::create(WStrToUTF8a(L"ÿ���ؿ���������Ϊ3,��Ŀ����Ϊ5,������һֱ�ۻ�."), "��Բ", 28);
	Content2->setColor(Color3B::ORANGE);
	Content2->setPosition(440, 420);
	this->addChild(Content2);

	auto Content3 = Label::create(WStrToUTF8a(L"ÿ����Ҫ������Ļ�ҷ������ķ��������ж�Ӧ�ĵ���."), "��Բ", 28);
	Content3->setColor(Color3B::ORANGE);
	Content3->setPosition(440, 380);
	this->addChild(Content3);

	auto Content4 = Label::create(WStrToUTF8a(L"ÿ�λ�����ȷ���ʼ�500��,���д��󵥴ʿ�500��,ײ���л���������1."), "��Բ", 28);
	Content4->setColor(Color3B::ORANGE);
	Content4->setPosition(480, 340);
	this->addChild(Content4);

	auto Content5 = Label::create(WStrToUTF8a(L"������Ϊ0,����������Ϊ0,���ߵ�һ�����еĵ����Ǵ����,��GameOver."), "��Բ", 28);
	Content5->setColor(Color3B::ORANGE);
	Content5->setPosition(480, 300);
	this->addChild(Content5);

	auto menu = Menu::create();
	this->addChild(menu);

	auto _BackMenu= MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt","Back to main menu"), CC_CALLBACK_1(Instruction::BackToMenu, this));
	_BackMenu->setPosition(0,-100);
	_BackMenu->setScale(0.7);
	_BackMenu->setColor(Color3B::ORANGE);
	menu->addChild(_BackMenu);
}
