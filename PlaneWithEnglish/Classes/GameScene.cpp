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
int count0 = 0;//���ü���
bool Ismoving = false;//�Ƿ����ƶ�
vector<char>vc;
bool IsShooting = false;//�Ƿ������
bool AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
Vec2 ShootPosition = Vec2(0,0);//�ӵ�������
bool IfBullet = false;//�Ƿ�����ӵ�
int remainlife = 3;//������
int score = 0;//����
bool IfPause = false;//�Ƿ���ͣ
char c0 = 'm';//������ͣ
int WordNum = 300;//���ʺ�
map<int, pair<wstring, string>>WordIndex;//���ڴ�ŵ�����Ϣ
int Stage = 1;//�ؿ���
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

std::string WStrToUTF8(const std::wstring& src)//���������������
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

void GameScene::Move(float f)//�Ի��ƶ�����
{
	auto EnemyRect = _Enemy->getBoundingBox();//��õл���������
	auto EnemyContent = _Enemy->getContentSize();//��õл����������С
	auto EnemyRect1 = _Enemy1->getBoundingBox();//��õл���������
	auto EnemyContent1 = _Enemy1->getContentSize();//��õл����������С
	auto EnemyRect2 = _Enemy2->getBoundingBox();//��õл���������
	auto EnemyContent2 = _Enemy2->getContentSize();//��õл����������С
	auto EnemyRect3 = _Enemy3->getBoundingBox();//��õл���������
	auto EnemyContent3 = _Enemy3->getContentSize();//��õл����������С

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

	if (EnemyRect.containsPoint(_MyPlane->getPosition()))//���л�ײ��
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
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
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
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
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
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
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
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
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
	//GameOver�͹��ص����
	log("Done!%d", WordIndex.size());
	if (IfScoreGet == true && score == 0)//���۷ֵ�0
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;//0��
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
	if (WordIndex.size() == 0)//��Ŀˢ��
	{
		Stage += 1;//�ؿ���+1
		auto scene = GamePassed::createScene();
		IfScoreChanged = true;
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1,scene));
	}
}

void  GameScene::Checked()
{
	auto EnemyRect = _Enemy->getBoundingBox();//��õл���������
	auto EnemyContent = _Enemy->getContentSize();//��õл����������С
	auto EnemyRect1 = _Enemy1->getBoundingBox();//��õл���������
	auto EnemyContent1 = _Enemy1->getContentSize();//��õл����������С
	auto EnemyRect2 = _Enemy2->getBoundingBox();//��õл���������
	auto EnemyContent2 = _Enemy2->getContentSize();//��õл����������С
	auto EnemyRect3 = _Enemy3->getBoundingBox();//��õл���������
	auto EnemyContent3 = _Enemy3->getContentSize();//��õл����������С

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto chioce = CCRANDOM_0_1() * 100;
	auto chioce0 = WordIndex.size();//ѡ����Ŀ������


	if (ShootPosition.x <= 5 || ShootPosition.x >= visibleSize.width - 320 ||
		ShootPosition.y <= 5 || ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		ShootPosition = Vec2(-10,-10);
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
	}
	else if (EnemyRect.containsPoint(ShootPosition))//��������˵л�
	{	
		//��Ҫ������ִ��map��erase����
		if (_Enemy->getTag() == WordNum)//WordNum�뵱ǰ��Ŀ��һһ��Ӧ
		{
			score += 500;
			//ɾ��WordNum��Ӧ�ؼ��ֵ�ֵ
			WordIndex.erase(WordNum);
			chioce0 -= 1;
			IfScoreGet = true;
			ScoreChecked();
		}
		else
		{//���д���ĵ���
			if (score != 0)
				score -= 500;//���۷�
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//�ӵ�����
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
		//WordNum�İ�����ÿһ��֮ǰ�ͱ���ʼ������
		//����map��size�仯ȷ��chioce0�ķ�Χ
		//������ȷ�������ǩ�����չʾ��ǩ����ô���ģ���map��ȡ��Ӧ�ĵ����ַ���
		for (auto i = 0; i != 5; ++i)
		{
			if (chioce0 == i )
			{
				WordNum = 300 + 5-i;
				WordNow->setString(WStrToUTF8(WordIndex2[5 - i]));
			}
		}
	}
	else if (EnemyRect1.containsPoint(ShootPosition))//��������˵л�
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
		{//���д���ĵ���
			if (score != 0)
				score -= 500;//���۷�
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//�ӵ�����
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
	else if (EnemyRect2.containsPoint(ShootPosition))//��������˵л�
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
		{//���д���ĵ���
			if (score != 0)
				score -= 500;//���۷�
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//�ӵ�����
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
	else if (EnemyRect3.containsPoint(ShootPosition))//��������˵л�
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
		{//���д���ĵ���
			if (score != 0)
				score -= 500;//���۷�
			else
				IfScoreGet = true;
			ScoreChecked();
		}
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		ShootPosition = Vec2(-10, -10);
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			_Bullet->setPosition(0, 0);
			_Bullet->removeFromParent();//�ӵ�����
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
{//����ú�����ÿ�ε��ù���������ӵ����飬��ɺ��Ƴ��ӵ�����
	Checked();//�����ӵ��ƶ�ǰ�ȼ��
	if (IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
						   //ͬʱҪ���ж����������Ҫ����ֹ
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
	else if (keyCode == EventKeyboard::KeyCode::KEY_J)//���
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
		//��ͣ��Ϸ
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
		//Ӧ�ø��ݵ����ڶ���Ԫ�ص�ֵ���жϷ���
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

void GameScene::EnemyMove(float f)//����л���ʱ�����˶�
{
	_Enemy->setPosition(_Enemy->getPosition().x, _Enemy->getPosition().y - 2);
	_Enemy1->setPosition(_Enemy1->getPosition().x, _Enemy1->getPosition().y - 2);
	_Enemy2->setPosition(_Enemy2->getPosition().x, _Enemy2->getPosition().y - 2);
	_Enemy3->setPosition(_Enemy3->getPosition().x, _Enemy3->getPosition().y - 2);
	EnemyAppearingFromTop(0);
}

void GameScene::EnemyAppearingFromTop(float f)//�л����´��Ͽճ���
{
	auto chioce = CCRANDOM_0_1() * 100;
	//��������˵ײ����֣��Զ���ʧ�����´��Ͽճ���
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

void GameScene::onEnterTransitionDidFinish()//���ɶ������
{
	Layer::onEnterTransitionDidFinish();
	auto Ori = Director::getInstance()->getVisibleOrigin();

	//�������ʼ��map
	if (Stage == 1)
	{//��һ����Ŀ��Ϣ
		WordIndex.insert(make_pair(300, make_pair(L"����,ʹ����", "galvanize.png")));
		WordIndex.insert(make_pair(301, make_pair(L"���ֵ�,���Դ����", "testing.png")));
		WordIndex.insert(make_pair(302, make_pair(L"��ĥ", "sap.png")));
		WordIndex.insert(make_pair(303, make_pair(L"���", "grunt.png"))); 
		WordIndex.insert(make_pair(304, make_pair(L"�ָ���", "revert.png")));

		WordNow = Label::create(WStrToUTF8(L"����,ʹ����"), "��Բ", 30);//��һ�����ʵ�������˼
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
		WordIndex.insert(make_pair(300, make_pair(L"����", "recount.png")));
		WordIndex.insert(make_pair(301, make_pair(L"��,����", "saddle.png")));
		WordIndex.insert(make_pair(302, make_pair(L"ʬ��", "corpse.png")));
		WordIndex.insert(make_pair(303, make_pair(L"���Դ����", "tricky.png")));
		WordIndex.insert(make_pair(304, make_pair(L"�䵭��", "detached.png")));

		WordNow = Label::create(WStrToUTF8(L"����"), "��Բ", 30);//��һ�����ʵ�������˼
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
		WordIndex.insert(make_pair(300, make_pair(L"����", "nudge.png")));
		WordIndex.insert(make_pair(301, make_pair(L"��Į", "apathy.png")));
		WordIndex.insert(make_pair(302, make_pair(L"����,��ͷɥ��", "slump.png")));
		WordIndex.insert(make_pair(303, make_pair(L"��������", "antidote.png")));
		WordIndex.insert(make_pair(304, make_pair(L"����ɶѵ�", "fraught.png")));

		WordNow = Label::create(WStrToUTF8(L"����"), "��Բ", 30);//��һ�����ʵ�������˼
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
		WordIndex.insert(make_pair(300, make_pair(L"����������", "upcoming.png")));
		WordIndex.insert(make_pair(301, make_pair(L"��ץ", "clutch.png")));
		WordIndex.insert(make_pair(302, make_pair(L"��������(��һ�׶�)", "proceed.png")));
		WordIndex.insert(make_pair(303, make_pair(L"����ʧ����", "chilling.png")));
		WordIndex.insert(make_pair(304, make_pair(L"̬��ǿӲ��", "pushy.png")));

		WordNow = Label::create(WStrToUTF8(L"����������"), "��Բ", 30);
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
		WordIndex.insert(make_pair(300, make_pair(L"���������", "disconcerting.png")));
		WordIndex.insert(make_pair(301, make_pair(L"���", "neglect.png")));
		WordIndex.insert(make_pair(302, make_pair(L"�໥����,����", "interact.png")));
		WordIndex.insert(make_pair(303, make_pair(L"����,չ��", "vista.png")));
		WordIndex.insert(make_pair(304, make_pair(L"����,�л�", "dialect.png")));

		WordNow = Label::create(WStrToUTF8(L"���������"), "��Բ", 30);
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
		WordIndex.insert(make_pair(300, make_pair(L"ɮ��", "monk.png")));
		WordIndex.insert(make_pair(301, make_pair(L"ʹ����,ʹ����", "enchant.png")));
		WordIndex.insert(make_pair(302, make_pair(L"�ų�", "exclude.png")));
		WordIndex.insert(make_pair(303, make_pair(L"�����,���ȵ�", "supremely.png")));
		WordIndex.insert(make_pair(304, make_pair(L"����,����,���", "confront.png")));

		WordNow = Label::create(WStrToUTF8(L"ɮ��"), "��Բ", 30);
		WordNow->setColor(Color3B::YELLOW);
		WordNow->setPosition(760, 350);
		this->addChild(WordNow);
		for (int i = 0; i != 5; ++i)
		{
			WordIndex1[i] = WordIndex[300 + i].second;
			WordIndex2[i] = WordIndex[300 + i].first;
		}
	}

	myPlane MyPlaneHandle;//�Ի������࣬�����Ի���Ϣ
	_MyPlane = Sprite::create(MyPlaneHandle.getPlanePicture());
	_MyPlane->setPosition(MyPlaneHandle.getMyPlanePoint());
	_MyPlane->setTag(MyPlaneHandle.getMyPlaneTag());
	this->addChild(_MyPlane,1);

	bullet MyBulletHandle;//�Ի��ӵ�������
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
	std::string ScoreText = ScoreValue.asString();//����ת��Ϊ�ַ���
	ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText);
	ScoreLabel->setPosition(Ori.x + 800, Ori.y + 500);
	ScoreLabel->setScale(0.7);
	this->addChild(ScoreLabel);

	Value LifeValue(remainlife);
	std::string LifeText = LifeValue.asString();//����ת��Ϊ�ַ���
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

	this->schedule(schedule_selector(GameScene::Move));//��ʱ�ƶ�
	this->schedule(schedule_selector(GameScene::Shoot), 0.012);//����ִ���ƶ����������
	this->schedule(schedule_selector(GameScene::EnemyMove));//�л��ƶ�����

	auto listener = EventListenerKeyboard::create();//���̼�����

	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);//���̰���ʱ���ƶ�
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);//�����ɿ�ʱ�Ĳ���

	auto eventdispatcher = Director::getInstance()->getEventDispatcher();
	eventdispatcher->addEventListenerWithSceneGraphPriority(listener,_MyPlane);
}

void GameScene::onExit()
{
	Layer::onExit();
	//���ó�ʼ��Ϣ
	IfScoreGet = false;
	if (!IfScoreChanged||remainlife==0)
		score = 0;//����
	remainlife = 3;//������

	IfPause = false;//�Ƿ���ͣ
	c = ' ';//���Ƽ���
	c0 = 'm';//������ͣ
	count0 = 0;//���ü���
	Ismoving = false;//�Ƿ����ƶ�
	WordNum = 300;//���ʺ�

}