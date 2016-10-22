#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "GameOver.h"
#include"GamePassed.h"
#include<vector>
#include<ctime>
#include<cstdlib>
#include<map>

using namespace std;
USING_NS_CC;

char c = ' ';
int count0 = 0;//引用计数
bool Ismoving = false;//是否在移动
vector<char>vc;
bool IsShooting = false;//是否在射击
bool AllowToShoot = true;//是否允许射击，一次只能射一个子弹
Vec2 ShootPosition = Vec2(0,0);//子弹的坐标
bool IfBullet = false;//是否存在子弹
int remainlife = 3;//生命数
int score = 0;//分数
bool IfPause = false;//是否暂停
char c0 = 'm';//控制暂停
int WordNum = 300;//单词号
map<int, pair<wstring, string>>WordIndex;//用于存放单词信息
int Stage = 1;//关卡数
string WordIndex1[5];
wstring WordIndex2[5];
bool IfScoreGet = false;
bool IfScoreChanged = false;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

std::string WStrToUTF8(const std::wstring& src)//解决中文乱码问题
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
		else if(w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if(w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if(sizeof(wchar_t) > 2 && w <= 0x10ffff)
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

void GameScene::Move(float f)//自机移动函数
{
	auto EnemyRect = _Enemy->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent = _Enemy->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect1 = _Enemy1->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent1 = _Enemy1->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect2 = _Enemy2->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent2 = _Enemy2->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect3 = _Enemy3->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent3 = _Enemy3->getContentSize();//获得敌机矩形区域大小

	auto chioce = CCRANDOM_0_1() * 100;

	auto Size = Director::getInstance()->getVisibleSize();

	if (c == 'd'&&Ismoving == true && _MyPlane->getPosition().x <= Size.width - 360)
	{
		_MyPlane->setPosition(_MyPlane->getPosition().x + 3, _MyPlane->getPosition().y);
	}
	else if (c == 'a'&&Ismoving == true && _MyPlane->getPosition().x >= 100)
	{
		_MyPlane->setPosition(_MyPlane->getPosition().x - 3, _MyPlane->getPosition().y);
	}
	else if (c == 's'&&Ismoving == true && _MyPlane->getPosition().y >= 100)
	{
		_MyPlane->setPosition(_MyPlane->getPosition().x, _MyPlane->getPosition().y - 3);
	}
	else if (c == 'w'&&Ismoving == true && _MyPlane->getPosition().y <= Size.height - 100)
	{
		_MyPlane->setPosition(_MyPlane->getPosition().x, _MyPlane->getPosition().y + 3);
	}

	if (EnemyRect.containsPoint(_MyPlane->getPosition()))//被敌机撞到
	{
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//分数转换为字符串
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		_MyPlane->setPosition(500, 120);

		_Enemy->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy = Sprite::create(WordIndex1[0]);
			_Enemy->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy = Sprite::create(WordIndex1[1]);
			_Enemy->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy = Sprite::create(WordIndex1[2]);
			_Enemy->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy = Sprite::create(WordIndex1[3]);
			_Enemy->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy = Sprite::create(WordIndex1[4]);
			_Enemy->setTag(304);
		}

		_Enemy->setPosition(100, 600);
		_Enemy->setScale(0.4);
		this->addChild(_Enemy);

		return;
	}
	else if (EnemyRect1.containsPoint(_MyPlane->getPosition()))
	{
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//分数转换为字符串
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		_MyPlane->setPosition(500, 120);

		_Enemy1->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy1 = Sprite::create(WordIndex1[0]);
			_Enemy1->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy1 = Sprite::create(WordIndex1[1]);
			_Enemy1->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy1 = Sprite::create(WordIndex1[2]);
			_Enemy1->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy1 = Sprite::create(WordIndex1[3]);
			_Enemy1->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy1= Sprite::create(WordIndex1[4]);
			_Enemy1->setTag(304);
		}

		_Enemy1->setPosition(200, 560);
		_Enemy1->setScale(0.4);
		this->addChild(_Enemy1);

		return;
	}
	else if (EnemyRect2.containsPoint(_MyPlane->getPosition()))
	{
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//分数转换为字符串
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);	
		
		_MyPlane->setPosition(500, 120);

		_Enemy2->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy2 = Sprite::create(WordIndex1[0]);
			_Enemy2->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy2 = Sprite::create(WordIndex1[1]);
			_Enemy2->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy2 = Sprite::create(WordIndex1[2]);
			_Enemy2->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy2 = Sprite::create(WordIndex1[3]);
			_Enemy2->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy2 = Sprite::create(WordIndex1[4]);
			_Enemy2->setTag(304);
		}

		_Enemy2->setPosition(300, 520);
		_Enemy2->setScale(0.4);
		this->addChild(_Enemy2);

		return;
	}
	else if (EnemyRect3.containsPoint(_MyPlane->getPosition()))
	{
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//分数转换为字符串
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		_MyPlane->setPosition(500, 120);

		_Enemy3->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy3 = Sprite::create(WordIndex1[0]);
			_Enemy3->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy3 = Sprite::create(WordIndex1[1]);
			_Enemy3->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy3 = Sprite::create(WordIndex1[2]);
			_Enemy3->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy3 = Sprite::create(WordIndex1[3]);
			_Enemy3->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy3 = Sprite::create(WordIndex1[4]);
			_Enemy3->setTag(304);
		}

		_Enemy3->setPosition(400, 560);
		_Enemy3->setScale(0.4);
		this->addChild(_Enemy3);

		return;
	}
}

void GameScene::ScoreChecked()
{
	//GameOver和过关的情况
	log("Done!%d", WordIndex.size());
	if (IfScoreGet == true && score == 0)//倒扣分到0
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;//0分
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
	if (WordIndex.size() == 0)//题目刷完
	{
		Stage += 1;//关卡数+1
		auto scene = GamePassed::createScene();
		IfScoreChanged = true;
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1,scene));
	}
}

void  GameScene::Checked()
{
	auto EnemyRect = _Enemy->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent = _Enemy->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect1 = _Enemy1->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent1 = _Enemy1->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect2 = _Enemy2->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent2 = _Enemy2->getContentSize();//获得敌机矩形区域大小
	auto EnemyRect3 = _Enemy3->getBoundingBox();//获得敌机矩形区域
	auto EnemyContent3 = _Enemy3->getContentSize();//获得敌机矩形区域大小

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto chioce = CCRANDOM_0_1() * 100;
	auto chioce0 = WordIndex.size();//选择题目的依据


	if (ShootPosition.x <= 5 || ShootPosition.x >= visibleSize.width - 320 ||
		ShootPosition.y <= 5 || ShootPosition.y >= visibleSize.height - 10)//如果到了边界
	{
		IsShooting = false;//停止射击
		AllowToShoot = true;//允许重新射击
		ShootPosition = Vec2(-10,-10);
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//子弹消除
			IfBullet = false;
		}
	}
	else if (EnemyRect.containsPoint(ShootPosition))//如果射中了敌机
	{	
		//需要在这里执行map的erase操作
		if (_Enemy->getTag() == WordNum)//WordNum与当前题目号一一对应
		{
			score += 500;
			//删除WordNum对应关键字的值
			WordIndex.erase(WordNum);
			chioce0 -= 1;
			IfScoreGet = true;
			ScoreChecked();
		}
		else
		{//击中错误的敌人
			if (score != 0)
				score -= 500;//倒扣分
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//分数转换为字符串
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//停止射击
		AllowToShoot = true;//允许重新射击
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//子弹消除
			IfBullet = false;
		}

		_Enemy->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy = Sprite::create(WordIndex1[0]);
			_Enemy->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy = Sprite::create(WordIndex1[1]);
			_Enemy->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy = Sprite::create(WordIndex1[2]);
			_Enemy->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy = Sprite::create(WordIndex1[3]);
			_Enemy->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy = Sprite::create(WordIndex1[4]);
			_Enemy->setTag(304);
		}

		_Enemy->setPosition(100, 600);
		_Enemy->setScale(0.4);
		this->addChild(_Enemy);
		//WordNum的安排在每一关之前就被初始化好了
		//根据map的size变化确定chioce0的范围
		//在这里确定问题标签下面的展示标签是怎么样的，用map提取对应的单词字符串
		for (auto i = 0; i != 5; ++i)
		{
			if (chioce0 == i )
			{
				WordNum = 300 + 5-i;
				WordNow->setString(WStrToUTF8(WordIndex2[5 - i]));
			}
		}
	}
	else if (EnemyRect1.containsPoint(ShootPosition))//如果射中了敌机
	{
		if (_Enemy1->getTag() == WordNum)
		{
			score += 500;
			WordIndex.erase(WordNum);
			chioce0 -= 1;
			IfScoreGet = true;
			ScoreChecked();
		}
		else
		{//击中错误的敌人
			if (score != 0)
				score -= 500;//倒扣分
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//分数转换为字符串
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//停止射击
		AllowToShoot = true;//允许重新射击
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//子弹消除
			IfBullet = false;
		}

		_Enemy1->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy1 = Sprite::create(WordIndex1[0]);
			_Enemy1->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy1 = Sprite::create(WordIndex1[1]);
			_Enemy1->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy1 = Sprite::create(WordIndex1[2]);
			_Enemy1->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy1 = Sprite::create(WordIndex1[3]);
			_Enemy1->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy1 = Sprite::create(WordIndex1[4]);
			_Enemy1->setTag(304);
		}

		_Enemy1->setPosition(200, 560);
		_Enemy1->setScale(0.4);
		this->addChild(_Enemy1);

		for (auto i = 0; i != 5; ++i)
		{
			if (chioce0 == i )
			{
				WordNum = 300 + 5 - i;
				WordNow->setString(WStrToUTF8(WordIndex2[5 - i]));
			}
		}
	}
	else if (EnemyRect2.containsPoint(ShootPosition))//如果射中了敌机
	{
		if (_Enemy2->getTag() == WordNum)
		{
			score += 500;
			WordIndex.erase(WordNum);
			chioce0 -= 1;
			IfScoreGet = true;
			ScoreChecked();
		}
		else
		{//击中错误的敌人
			if (score != 0)
				score -= 500;//倒扣分
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//分数转换为字符串
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//停止射击
		AllowToShoot = true;//允许重新射击
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//子弹消除
			IfBullet = false;
		}

		_Enemy2->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy2 = Sprite::create(WordIndex1[0]);
			_Enemy2->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy2 = Sprite::create(WordIndex1[1]);
			_Enemy2->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy2 = Sprite::create(WordIndex1[2]);
			_Enemy2->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy2 = Sprite::create(WordIndex1[3]);
			_Enemy2->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy2 = Sprite::create(WordIndex1[4]);
			_Enemy2->setTag(304);
		}

		_Enemy2->setPosition(300, 520);
		_Enemy2->setScale(0.4);
		this->addChild(_Enemy2);
		for (auto i = 0; i != 5; ++i)
		{
			if (chioce0 == i )
			{
				WordNum = 300 + 5 - i;
				WordNow->setString(WStrToUTF8(WordIndex2[5 - i]));
			}
		}
	}
	else if (EnemyRect3.containsPoint(ShootPosition))//如果射中了敌机
	{
		if (_Enemy3->getTag() == WordNum)
		{
			score += 500;
			WordIndex.erase(WordNum);
			chioce0 -= 1;
			IfScoreGet = true;
			ScoreChecked();
		}
		else
		{//击中错误的敌人
			if (score != 0)
				score -= 500;//倒扣分
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//分数转换为字符串
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//停止射击
		AllowToShoot = true;//允许重新射击
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//子弹消除
			IfBullet = false;
		}

		_Enemy3->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy3 = Sprite::create(WordIndex1[0]);
			_Enemy3->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy3 = Sprite::create(WordIndex1[1]);
			_Enemy3->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy3 = Sprite::create(WordIndex1[2]);
			_Enemy3->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy3 = Sprite::create(WordIndex1[3]);
			_Enemy3->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy3 = Sprite::create(WordIndex1[4]);
			_Enemy3->setTag(304);
		}

		_Enemy3->setPosition(400, 560);
		_Enemy3->setScale(0.4);
		this->addChild(_Enemy3);

		for (auto i = 0; i != 5; ++i)
		{
			if (chioce0 == i )
			{
				WordNum = 300 + 5 -i;
				WordNow->setString(WStrToUTF8(WordIndex2[5 - i]));
			}
		}
	}
}


void GameScene::Shoot(float f)
{//射击用函数，每次调用过程先添加子弹精灵，完成后移除子弹精灵
	Checked();//进行子弹移动前先检查
	if (IsShooting == true)//如果状态为正在射击，就不断增加子弹的某个坐标
						   //同时要有判断哪里射击需要被中止
	{
		ShootPosition.y += 3;
		_Bullet->setPosition(ShootPosition.x, ShootPosition.y);
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pevent)
{
	auto sp = static_cast<Sprite *>(pevent->getCurrentTarget());
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		c = 'd';
		++count0;
		vc.push_back(c);
		Ismoving = true;
		if (!IfPause) { c0 = 'm'; }
		else { c0 = ' '; }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		c = 'a';
		++count0;
		vc.push_back(c);
		Ismoving = true;
		if (!IfPause) { c0 = 'm'; }
		else { c0 = ' '; }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		c = 's';
		++count0;
		vc.push_back(c);
		Ismoving = true;
		if (IfPause) { c0 = 'm'; }
		else { c0 = ' '; }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		c = 'w';
		++count0;
		vc.push_back(c);
		Ismoving = true;
		if (!IfPause) { c0 = 'm'; }
		else { c0 = ' '; }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J)//射击
	{
		if (AllowToShoot)
		{
			IsShooting = true;
			AllowToShoot = false;
			ShootPosition = _MyPlane->getPosition();
			_Bullet->setPosition(0, 0);
			this->addChild(_Bullet);
			IfBullet = true;
		}
		if (!IfPause) { c0 = 'm'; }
		else { c0 = ' '; }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_P)
	{
		//暂停游戏
		if (c0 == 'm')
		{
			Director::getInstance()->pause();
			c0 = ' ';
			IfPause = true;
		}
		else if (c0 == ' ')
		{
			Director::getInstance()->resume();
			c0 = 'm';
			IfPause = false;
		}
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *pevent)
{
	if (keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_W || 
		keycode == EventKeyboard::KeyCode::KEY_S || keycode == EventKeyboard::KeyCode::KEY_A)
	{
		//应该根据倒数第二个元素的值来判断方向
		char temp = ' ';
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_D:temp = 'd'; break;
		case EventKeyboard::KeyCode::KEY_W:temp = 'w'; break;
		case EventKeyboard::KeyCode::KEY_S:temp = 's'; break;
		case EventKeyboard::KeyCode::KEY_A:temp = 'a'; break;
		}
		count0--;
		auto bg = vc.begin();
		if (bg != vc.end())
		{
			for (auto it = bg; it != vc.end();)
			{
				if (*it == temp)
					it=vc.erase(it);
				else ++it;
			}
		}
		if (bg != vc.end())
		{
			c = *(vc.end() - 1);
		}
	}
	if (count0 <= 0)
		Ismoving = false;
	if (count0 <= 0)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_D: {c = 'd'; if (!IfPause) { c0 = 'm'; } else { c0 = ' '; }} break;
		case EventKeyboard::KeyCode::KEY_W: {c = 'w'; if (!IfPause) { c0 = 'm'; } else { c0 = ' '; }} break;
		case EventKeyboard::KeyCode::KEY_S: {c = 's'; if (!IfPause) { c0 = 'm'; } else { c0 = ' '; }}break;
		case EventKeyboard::KeyCode::KEY_A: {c = 'a'; if (!IfPause) { c0 = 'm'; } else { c0 = ' '; }} break;
		case EventKeyboard::KeyCode::KEY_J: { if (!IfPause) { c0 = 'm'; } else { c0 = ' '; } }; break;
		}
	}
}

void GameScene::BackToMenu(Ref *ref)
{
	score = 0;
	remainlife = 3;
	Director::getInstance()->resume();
	c0 = 'm';
	IfPause = false;
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::EnemyMove(float f)//五个敌机定时匀速运动
{
	_Enemy->setPosition(_Enemy->getPosition().x, _Enemy->getPosition().y - 2);
	_Enemy1->setPosition(_Enemy1->getPosition().x, _Enemy1->getPosition().y - 2);
	_Enemy2->setPosition(_Enemy2->getPosition().x, _Enemy2->getPosition().y - 2);
	_Enemy3->setPosition(_Enemy3->getPosition().x, _Enemy3->getPosition().y - 2);
	EnemyAppearingFromTop(0);
}

void GameScene::EnemyAppearingFromTop(float f)//敌机重新从上空出现
{
	auto chioce = CCRANDOM_0_1() * 100;
	//如果超过了底部部分，自动消失，重新从上空出现
	if (_Enemy->getPosition().y <= 50)
	{
		_Enemy->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy = Sprite::create(WordIndex1[0]);
			_Enemy->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy = Sprite::create(WordIndex1[1]);
			_Enemy->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy = Sprite::create(WordIndex1[2]);
			_Enemy->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy = Sprite::create(WordIndex1[3]);
			_Enemy->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy = Sprite::create(WordIndex1[4]);
			_Enemy->setTag(304);
		}

		_Enemy->setPosition(100, 600);
		_Enemy->setScale(0.4);
		this->addChild(_Enemy);
	}
	else if (_Enemy1->getPosition().y <= 50)
	{
		_Enemy1->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy1 = Sprite::create(WordIndex1[0]);
			_Enemy1->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy1 = Sprite::create(WordIndex1[1]);
			_Enemy1->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy1 = Sprite::create(WordIndex1[2]);
			_Enemy1->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy1 = Sprite::create(WordIndex1[3]);
			_Enemy1->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy1 = Sprite::create(WordIndex1[4]);
			_Enemy1->setTag(304);
		}
		_Enemy1->setPosition(200, 560);
		_Enemy1->setScale(0.4);
		this->addChild(_Enemy1);
	}
	else if (_Enemy2->getPosition().y <= 50)
	{
		_Enemy2->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy2 = Sprite::create(WordIndex1[0]);
			_Enemy2->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy2 = Sprite::create(WordIndex1[1]);
			_Enemy2->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy2 = Sprite::create(WordIndex1[2]);
			_Enemy2->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy2 = Sprite::create(WordIndex1[3]);
			_Enemy2->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy2 = Sprite::create(WordIndex1[4]);
			_Enemy2->setTag(304);
		}

		_Enemy2->setPosition(300,520);
		_Enemy2->setScale(0.4);
		this->addChild(_Enemy2);
	}
	else if (_Enemy3->getPosition().y <= 50)
	{
		_Enemy3->removeFromParent();
		if (chioce >= 0 && chioce <= 20)
		{
			_Enemy3 = Sprite::create(WordIndex1[0]);
			_Enemy3->setTag(300);
		}
		else if (chioce > 20 && chioce <= 40)
		{
			_Enemy3 = Sprite::create(WordIndex1[1]);
			_Enemy3->setTag(301);
		}
		else if (chioce > 40 && chioce <= 60)
		{
			_Enemy3 = Sprite::create(WordIndex1[2]);
			_Enemy3->setTag(302);
		}
		else if (chioce > 60 && chioce <= 80)
		{
			_Enemy3 = Sprite::create(WordIndex1[3]);
			_Enemy3->setTag(303);
		}
		else if (chioce > 80 && chioce <= 100)
		{
			_Enemy3 = Sprite::create(WordIndex1[4]);
			_Enemy3->setTag(304);
		}

		
		_Enemy3->setPosition(400, 560);
		_Enemy3->setScale(0.4);
		this->addChild(_Enemy3);
	}
}


// on "init" you need to initialize your instance
bool GameScene::init()
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

void GameScene::onEnterTransitionDidFinish()//过渡动画完成
{
	Layer::onEnterTransitionDidFinish();
	auto Ori = Director::getInstance()->getVisibleOrigin();

	//在这里初始化map
	if (Stage == 1)
	{//第一关题目信息
		WordIndex.insert(make_pair(300, make_pair(L"鼓励,使振作", "galvanize.png")));
		WordIndex.insert(make_pair(301, make_pair(L"棘手的,难以处理的", "testing.png")));
		WordIndex.insert(make_pair(302, make_pair(L"消磨", "sap.png")));
		WordIndex.insert(make_pair(303, make_pair(L"嘟囔", "grunt.png"))); 
		WordIndex.insert(make_pair(304, make_pair(L"恢复到", "revert.png")));

		WordNow = Label::create(WStrToUTF8(L"鼓励,使振作"), "幼圆", 30);//第一个单词的中文意思
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}
	else if (Stage == 2)
	{
		WordIndex.insert(make_pair(300, make_pair(L"叙述", "recount.png")));
		WordIndex.insert(make_pair(301, make_pair(L"马鞍,车座", "saddle.png")));
		WordIndex.insert(make_pair(302, make_pair(L"尸体", "corpse.png")));
		WordIndex.insert(make_pair(303, make_pair(L"难以处理的", "tricky.png")));
		WordIndex.insert(make_pair(304, make_pair(L"冷淡的", "detached.png")));

		WordNow = Label::create(WStrToUTF8(L"叙述"), "幼圆", 30);//第一个单词的中文意思
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}
	else if (Stage == 3)
	{
		WordIndex.insert(make_pair(300, make_pair(L"轻推", "nudge.png")));
		WordIndex.insert(make_pair(301, make_pair(L"冷漠", "apathy.png")));
		WordIndex.insert(make_pair(302, make_pair(L"暴跌,垂头丧气", "slump.png")));
		WordIndex.insert(make_pair(303, make_pair(L"矫正方法", "antidote.png")));
		WordIndex.insert(make_pair(304, make_pair(L"问题成堆的", "fraught.png")));

		WordNow = Label::create(WStrToUTF8(L"轻推"), "幼圆", 30);//第一个单词的中文意思
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}
	else if (Stage == 4)
	{
		WordIndex.insert(make_pair(300, make_pair(L"即将到来的", "upcoming.png")));
		WordIndex.insert(make_pair(301, make_pair(L"紧抓", "clutch.png")));
		WordIndex.insert(make_pair(302, make_pair(L"继续进行(下一阶段)", "proceed.png")));
		WordIndex.insert(make_pair(303, make_pair(L"令人失望的", "chilling.png")));
		WordIndex.insert(make_pair(304, make_pair(L"态度强硬的", "pushy.png")));

		WordNow = Label::create(WStrToUTF8(L"即将到来的"), "幼圆", 30);
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}
	else if (Stage == 5)
	{
		WordIndex.insert(make_pair(300, make_pair(L"令人困惑的", "disconcerting.png")));
		WordIndex.insert(make_pair(301, make_pair(L"疏忽", "neglect.png")));
		WordIndex.insert(make_pair(302, make_pair(L"相互交流,互动", "interact.png")));
		WordIndex.insert(make_pair(303, make_pair(L"美景,展望", "vista.png")));
		WordIndex.insert(make_pair(304, make_pair(L"方言,行话", "dialect.png")));

		WordNow = Label::create(WStrToUTF8(L"令人困惑的"), "幼圆", 30);
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}
	else if (Stage == 6)
	{
		WordIndex.insert(make_pair(300, make_pair(L"僧侣", "monk.png")));
		WordIndex.insert(make_pair(301, make_pair(L"使入迷,使陶醉", "enchant.png")));
		WordIndex.insert(make_pair(302, make_pair(L"排斥", "exclude.png")));
		WordIndex.insert(make_pair(303, make_pair(L"极其地,极度地", "supremely.png")));
		WordIndex.insert(make_pair(304, make_pair(L"正视,处理,面对", "confront.png")));

		WordNow = Label::create(WStrToUTF8(L"僧侣"), "幼圆", 30);
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}

	myPlane MyPlaneHandle;//自机操作类，包含自机信息
	_MyPlane = Sprite::create(MyPlaneHandle.getPlanePicture());
	_MyPlane->setPosition(MyPlaneHandle.getMyPlanePoint());
	_MyPlane->setTag(MyPlaneHandle.getMyPlaneTag());
	this->addChild(_MyPlane,1);

	bullet MyBulletHandle;//自机子弹操作类
	_Bullet = Sprite::create(MyBulletHandle.getBulletPicture());
	_Bullet->setPosition(MyBulletHandle.getBulletPoint());
	_Bullet->setTag(MyBulletHandle.getBulletTag());
	this->addChild(_Bullet,1);

	_Enemy = Sprite::create(WordIndex1[4]);
	_Enemy->setPosition(100, 600);
	_Enemy->setScale(0.4);
	_Enemy->setTag(304);
	this->addChild(_Enemy, 0);

	_Enemy1 = Sprite::create(WordIndex1[0]);
	_Enemy1->setPosition(200, 560);
	_Enemy1->setScale(0.4);
	_Enemy1->setTag(300);
	this->addChild(_Enemy1, 0);

	_Enemy2 = Sprite::create(WordIndex1[2]);
	_Enemy2->setPosition(300, 520);
	_Enemy2->setScale(0.4);
	_Enemy2->setTag(302);
	this->addChild(_Enemy2, 0);

	_Enemy3 = Sprite::create(WordIndex1[3]);
	_Enemy3->setPosition(400, 560);
	_Enemy3->setScale(0.4);
	_Enemy3->setTag(303);
	this->addChild(_Enemy3, 0);

	auto menu = Menu::create();
	this->addChild(menu);
	auto _BackMenu = MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt","Back to main menu"), CC_CALLBACK_1(GameScene::BackToMenu, this));
	_BackMenu->setPosition(Ori.x+320,Ori.y+250);
	_BackMenu->setScale(0.7);
	menu->addChild(_BackMenu);

	Value ScoreValue(score);
	std::string ScoreText = ScoreValue.asString();//分数转换为字符串
	ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText);
	ScoreLabel->setPosition(Ori.x + 800, Ori.y + 500);
	ScoreLabel->setScale(0.7);
	this->addChild(ScoreLabel);

	Value LifeValue(remainlife);
	std::string LifeText = LifeValue.asString();//分数转换为字符串
	LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText);
	LifeLabel->setPosition(Ori.x + 800, Ori.y + 450);
	LifeLabel->setScale(0.7);
	this->addChild(LifeLabel);

	auto ScoreInform = Label::createWithBMFont("futura-48.fnt", "Score ");
	ScoreInform->setScale(0.7);
	ScoreInform->setPosition(Ori.x + 700, Ori.y + 500);
	this->addChild(ScoreInform);

	auto LifeInform = Label::createWithBMFont("futura-48.fnt", "Life  ");
	LifeInform->setScale(0.7);
	LifeInform->setPosition(Ori.x + 700, Ori.y + 450);
	this->addChild(LifeInform);

	auto QuestionLabel = Label::createWithBMFont("futura-48.fnt", "The Chinese meaning");
	QuestionLabel->setColor(Color3B::YELLOW);
	QuestionLabel->setPosition(790, 400);
	QuestionLabel->setScale(0.7);
	this->addChild(QuestionLabel);

	this->schedule(schedule_selector(GameScene::Move));//定时移动
	this->schedule(schedule_selector(GameScene::Shoot), 0.012);//定制执行移动和射击函数
	this->schedule(schedule_selector(GameScene::EnemyMove));//敌机移动函数

	auto listener = EventListenerKeyboard::create();//键盘监听器

	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);//键盘按下时的移动
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);//键盘松开时的操作

	auto eventdispatcher = Director::getInstance()->getEventDispatcher();
	eventdispatcher->addEventListenerWithSceneGraphPriority(listener,_MyPlane);
}

void GameScene::onExit()
{
	Layer::onExit();
	//重置初始信息
	IfScoreGet = false;
	if (!IfScoreChanged||remainlife==0)
		score = 0;//分数
	remainlife = 3;//生命数

	IfPause = false;//是否暂停
	c = ' ';//控制键盘
	c0 = 'm';//控制暂停
	count0 = 0;//引用计数
	Ismoving = false;//是否在移动
	WordNum = 300;//单词号

}