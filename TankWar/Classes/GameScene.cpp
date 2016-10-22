#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "GameOver.h"
#include <vector>
#include "GameScene2.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace std;
using namespace cocostudio::timeline;
USING_NS_CC;

int remainlife = 3;//������
int score = 0;//����
bool IfPause = false;//�Ƿ���ͣ
char c = ' ';//���Ƽ���
char c0 = 'm';//������ͣ
int count0 = 0;//���ü���
bool Ismoving = false;//�Ƿ����ƶ�
vector<char>vc;

Vec2 MyPresentPoint = Vec2(18.0f,54.0f);
bool IsShooting = false;//�Ƿ������
bool AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
int MyRotation = 0;//�Լ��ĽǶȣ����ڸ������
Vec2 ShootPosition = Vec2(110,110);//�ӵ�������
bool IfBullet=false;//�Ƿ�����ӵ�

Vec2 EnemyPresentPoint1=Vec2((44 + 11/2) * 3, (44 + 11 / 2) * 3);
Vec2 Enemy1ShootPosition = Vec2(110, 44);//����1���ӵ�����
bool IfEnemy1Bullet = false;//�Ƿ���ڵ���1���ӵ�
bool Enemy1IsShooting = false;//�Ƿ������
bool Enemy1AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
int Enemy1Rotation = 0;//�л�1�ĽǶ�

Vec2 EnemyPresentPoint2 = Vec2((110 + 11 / 2) * 3, (44 + 11 / 2) * 3);
Vec2 Enemy2ShootPosition = Vec2(110, 44);//����2���ӵ�����
bool IfEnemy2Bullet = false;//�Ƿ���ڵ���2���ӵ�
bool Enemy2IsShooting = false;//�Ƿ������
bool Enemy2AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
int Enemy2Rotation = 0;//�л�2�ĽǶ�

Vec2 EnemyPresentPoint3 = Vec2((176 + 11 / 2) * 3, (44 + 11 / 2) * 3);
Vec2 Enemy3ShootPosition = Vec2(110, 44);//����3���ӵ�����
bool IfEnemy3Bullet = false;//�Ƿ���ڵ���3���ӵ�
bool Enemy3IsShooting = false;//�Ƿ������
bool Enemy3AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
int Enemy3Rotation = 0;//�л�3�ĽǶ�

Vec2 EnemyPresentPoint4 = Vec2((110 + 11 / 2) * 3, (110 + 11 / 2) * 3);
Vec2 Enemy4ShootPosition = Vec2(110, 44);//����4���ӵ�����
bool IfEnemy4Bullet = false;//�Ƿ���ڵ���4���ӵ�
bool Enemy4IsShooting = false;//�Ƿ������
bool Enemy4AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
int Enemy4Rotation = 0;//�л�4�ĽǶ�

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

void GameScene::BackToMenu(Ref *ref)
{
	remainlife = 3;//������
	score = 0;//����
	IfPause = false;//�Ƿ���ͣ
	c = ' ';//���Ƽ���
	c0 = 'm';//������ͣ
	count0 = 0;//���ü���
	Ismoving = false;//�Ƿ����ƶ�

	MyPresentPoint = Vec2(18.0f, 54.0f);
	IsShooting = false;//�Ƿ������
	AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	MyRotation = 0;//�Լ��ĽǶȣ����ڸ������
	ShootPosition = Vec2(110, 110);//�ӵ�������
	IfBullet = false;//�Ƿ�����ӵ�

	EnemyPresentPoint1 = Vec2((44 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy1ShootPosition = Vec2(110, 44);//����1���ӵ�����
	IfEnemy1Bullet = false;//�Ƿ���ڵ���1���ӵ�
	Enemy1IsShooting = false;//�Ƿ������
	Enemy1AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy1Rotation = 0;//�л�1�ĽǶ�

	EnemyPresentPoint2 = Vec2((110 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy2ShootPosition = Vec2(110, 44);//����2���ӵ�����
	IfEnemy2Bullet = false;//�Ƿ���ڵ���2���ӵ�
	Enemy2IsShooting = false;//�Ƿ������
	Enemy2AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy2Rotation = 0;//�л�2�ĽǶ�

	EnemyPresentPoint3 = Vec2((176 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy3ShootPosition = Vec2(110, 44);//����3���ӵ�����
	IfEnemy3Bullet = false;//�Ƿ���ڵ���3���ӵ�
	Enemy3IsShooting = false;//�Ƿ������
	Enemy3AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy3Rotation = 0;//�л�3�ĽǶ�

	EnemyPresentPoint4 = Vec2((110 + 11 / 2) * 3, (110 + 11 / 2) * 3);
	Enemy4ShootPosition = Vec2(110, 44);//����4���ӵ�����
	IfEnemy4Bullet = false;//�Ƿ���ڵ���4���ӵ�
	Enemy4IsShooting = false;//�Ƿ������
	Enemy4AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy4Rotation = 0;//�л�4�ĽǶ�

	Scene * scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::ScoreChecked()
{//�������������Ƿ������һ���ؿ�
	if (score == 2500)
	{
		auto scene=GameScene2::createScene();
		IfScoreChanged = true;
		Director::getInstance()->replaceScene(TransitionFadeBL::create(3,scene));
	}
	else if (score == 6000)
	{
		auto scene = GameScene2::createScene();
		IfScoreChanged = true;
		Director::getInstance()->replaceScene(TransitionFadeBL::create(3, scene));
	}
}

void GameScene::Checked()//�����Ի����е��˺ͱ߽�ĺ���
{
	Size EnemyContent1 = Enemy1->getContentSize();
	Size EnemyContent2 = Enemy1->getContentSize();
	Size EnemyContent3 = Enemy1->getContentSize();
	Size EnemyContent4 = Enemy1->getContentSize();//����ĸ��л��ĳߴ�

	Rect EnemyRect1 = Rect(0, 0, EnemyContent1.width, EnemyContent1.height);
	Rect EnemyRect2 = Rect(0, 0, EnemyContent2.width, EnemyContent2.height);
	Rect EnemyRect3 = Rect(0, 0, EnemyContent3.width, EnemyContent3.height);
	Rect EnemyRect4 = Rect(0, 0, EnemyContent4.width, EnemyContent4.height);//����ĸ��л��ľ��η�Χ

	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (ShootPosition.x <= 5 || ShootPosition.x >= visibleSize.width - 320 || ShootPosition.y <= 5 || ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		ShootPosition = MyTank->getPosition();
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
	}
	else if (ShootPosition.x>=115*3&&ShootPosition.x<=128*3&&ShootPosition.y>=11*3&&ShootPosition.y<=3*22)//���д�Ӫ GameOver
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
	else if (EnemyRect1.containsPoint(Enemy1->convertToNodeSpace(ShootPosition)))//ע����Ҫת��Ϊģ������
	{//��������˵���
		score += 500;//��������
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition( 800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		ShootPosition = MyTank->getPosition();
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{ 
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		Enemy1->setPosition((44 + _tileMap->getTileSize().width / 2) * 3, (44 - _tileMap->getTileSize().height / 2) * 3);
		Enemy1->setScale(3);
		ScoreChecked();
	}
	else if (EnemyRect2.containsPoint(Enemy2->convertToNodeSpace(ShootPosition)))
	{
		//��������˵���
		score += 500;
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");	
		ShootPosition = MyTank->getPosition();
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		Enemy2->setPosition((110 + _tileMap->getTileSize().width / 2) * 3, (44 + _tileMap->getTileSize().height / 2) * 3);
		Enemy2->setScale(3);
		ScoreChecked();
	}
	else if (EnemyRect3.containsPoint(Enemy3->convertToNodeSpace(ShootPosition)))
	{
		//��������˵���
		score += 500;
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		ShootPosition = MyTank->getPosition();
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		Enemy3->setPosition((176 + _tileMap->getTileSize().width / 2) * 3, (44 + _tileMap->getTileSize().height / 2) * 3);
		Enemy3->setScale(3);
		ScoreChecked();
	}
	else if (EnemyRect4.containsPoint(Enemy4->convertToNodeSpace(ShootPosition)))
	{
		//��������˵���
		score += 500;
		this->removeChild(ScoreLabel);
		Value ScoreValue1(score);
		std::string ScoreText1 = ScoreValue1.asString();//����ת��Ϊ�ַ���
		ScoreLabel = Label::createWithBMFont("futura-48.fnt", ScoreText1);
		ScoreLabel->setPosition(800, 500);
		ScoreLabel->setScale(0.7);
		this->addChild(ScoreLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");	
		ShootPosition = MyTank->getPosition();
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		Enemy4->setPosition((110 + 7 * _tileMap->getTileSize().width / 2) * 3, (110 + 7 * _tileMap->getTileSize().height / 2) * 3);
		Enemy4->setScale(3);
		ScoreChecked();
	}

	else if (abs(ShootPosition.x-Enemy1ShootPosition.x)<=5&& abs(ShootPosition.y - Enemy1ShootPosition.y) <= 5)//�ӵ������Ĵ���
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		ShootPosition = MyTank->getPosition();
		Enemy1ShootPosition = Enemy1->getPosition();
		Enemy1IsShooting = false;//ֹͣ���
		Enemy1AllowToShoot = true;//�����������
		if (IfEnemy1Bullet)
		{
			Enemybullet1->setPosition(0, 0);
			Enemybullet1->removeFromParent();//�ӵ�����
			IfEnemy1Bullet = false;
		}
	}
	else if (abs(ShootPosition.x - Enemy2ShootPosition.x) <= 5 && abs(ShootPosition.y - Enemy2ShootPosition.y) <= 5)
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		ShootPosition = MyTank->getPosition();
		Enemy2ShootPosition = Enemy2->getPosition();
		Enemy2IsShooting = false;//ֹͣ���
		Enemy2AllowToShoot = true;//�����������
		if (IfEnemy2Bullet)
		{
			Enemybullet2->setPosition(0, 0);
			Enemybullet2->removeFromParent();//�ӵ�����
			IfEnemy2Bullet = false;
		}
	}
	else if (abs(ShootPosition.x - Enemy3ShootPosition.x) <= 5 && abs(ShootPosition.y - Enemy3ShootPosition.y) <= 5)
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		ShootPosition = MyTank->getPosition();
		Enemy3ShootPosition = Enemy3->getPosition();
		Enemy3IsShooting = false;//ֹͣ���
		Enemy3AllowToShoot = true;//�����������
		if (IfEnemy3Bullet)
		{
			Enemybullet3->setPosition(0, 0);
			Enemybullet3->removeFromParent();//�ӵ�����
			IfEnemy3Bullet = false;
		}
	}
	else if (abs(ShootPosition.x - Enemy4ShootPosition.x) <= 5 && abs(ShootPosition.y - Enemy4ShootPosition.y) <= 5)
	{
		IsShooting = false;//ֹͣ���
		AllowToShoot = true;//�����������
		if (IfBullet)
		{
			bullet->setPosition(0, 0);
			bullet->removeFromParent();//�ӵ�����
			IfBullet = false;
		}
		ShootPosition = MyTank->getPosition();
		Enemy4ShootPosition = Enemy4->getPosition();
		Enemy4IsShooting = false;//ֹͣ���
		Enemy4AllowToShoot = true;//�����������
		if (IfEnemy4Bullet)
		{
			Enemybullet4->setPosition(0, 0);
			Enemybullet4->removeFromParent();//�ӵ�����
			IfEnemy4Bullet = false;
		}
	}
}

void GameScene::EnemyChecked1(float f)
{
	Size MyTankContent = MyTank->getContentSize();
	Rect MyTankRect = Rect(0, 0, MyTankContent.width, MyTankContent.height);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (Enemy1ShootPosition.x <= 5 || Enemy1ShootPosition.x >= visibleSize.width - 320 || Enemy1ShootPosition.y <= 5 || Enemy1ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		Enemy1ShootPosition = Enemy1->getPosition();
		Enemy1IsShooting = false;//ֹͣ���
		Enemy1AllowToShoot = true;//�����������
		if (IfEnemy1Bullet)
		{
			Enemybullet1->setPosition(0, 0);
			Enemybullet1->removeFromParent();//�ӵ�����
			IfEnemy1Bullet = false;
		}
	}
	else if (MyTankRect.containsPoint(MyTank->convertToNodeSpace(Enemy1ShootPosition)))//ע����Ҫת��Ϊģ������
	{//����������Ի�
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		
		Enemy1IsShooting = false;//ֹͣ���
		Enemy1AllowToShoot = true;//�����������
		if (IfEnemy1Bullet)
		{
			Enemybullet1->setPosition(0, 0);
			Enemybullet1->removeFromParent();//�ӵ�����
			IfEnemy1Bullet = false;
		}
		MyTank->setPosition(Vec2((11+_tileMap->getTileSize().width/2)*3, (11 + _tileMap->getTileSize().height / 2) * 3));
	}
	else if (Enemy1ShootPosition.x >= 115 * 3 && Enemy1ShootPosition.x <= 128 * 3 && Enemy1ShootPosition.y >= 11 * 3 && Enemy1ShootPosition.y <= 3 * 22)//���д�Ӫ GameOver
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
}
void GameScene::EnemyChecked2(float f)
{
	Size MyTankContent = MyTank->getContentSize();
	Rect MyTankRect = Rect(0, 0, MyTankContent.width, MyTankContent.height);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (Enemy2ShootPosition.x <= 5 || Enemy2ShootPosition.x >= visibleSize.width - 320 || Enemy2ShootPosition.y <= 5 || Enemy2ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		Enemy2ShootPosition = Enemy2->getPosition();
		Enemy2IsShooting = false;//ֹͣ���
		Enemy2AllowToShoot = true;//�����������
		if (IfEnemy2Bullet)
		{
			Enemybullet2->setPosition(0, 0);
			Enemybullet2->removeFromParent();//�ӵ�����
			IfEnemy2Bullet = false;
		}
	}
	else if (MyTankRect.containsPoint(MyTank->convertToNodeSpace(Enemy2ShootPosition)))//ע����Ҫת��Ϊģ������
	{//����������Ի�
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		Enemy2IsShooting = false;//ֹͣ���
		Enemy2AllowToShoot = true;//�����������
		if (IfEnemy2Bullet)
		{
			Enemybullet2->setPosition(0, 0);
			Enemybullet2->removeFromParent();//�ӵ�����
			IfEnemy2Bullet = false;
		}
		MyTank->setPosition(Vec2((11 + _tileMap->getTileSize().width / 2) * 3, (11 + _tileMap->getTileSize().height / 2) * 3));
	}
	else if (Enemy2ShootPosition.x >= 115 * 3 && Enemy2ShootPosition.x <= 128 * 3 && Enemy2ShootPosition.y >= 11 * 3 && Enemy2ShootPosition.y <= 3 * 22)//���д�Ӫ GameOver
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
}

void GameScene::EnemyChecked3(float f)
{
	Size MyTankContent = MyTank->getContentSize();
	Rect MyTankRect = Rect(0, 0, MyTankContent.width, MyTankContent.height);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (Enemy3ShootPosition.x <= 5 || Enemy3ShootPosition.x >= visibleSize.width - 320 || Enemy3ShootPosition.y <= 5 || Enemy3ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		Enemy3ShootPosition = Enemy3->getPosition();
		Enemy3IsShooting = false;//ֹͣ���
		Enemy3AllowToShoot = true;//�����������
		if (IfEnemy3Bullet)
		{
			Enemybullet3->setPosition(0, 0);
			Enemybullet3->removeFromParent();//�ӵ�����
			IfEnemy3Bullet = false;
		}
	}
	else if (MyTankRect.containsPoint(MyTank->convertToNodeSpace(Enemy3ShootPosition)))//ע����Ҫת��Ϊģ������
	{//����������Ի�
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		Enemy3IsShooting = false;//ֹͣ���
		Enemy3AllowToShoot = true;//�����������
		if (IfEnemy3Bullet)
		{
			Enemybullet3->setPosition(0, 0);
			Enemybullet3->removeFromParent();//�ӵ�����
			IfEnemy3Bullet = false;
		}
		MyTank->setPosition(Vec2((11 + _tileMap->getTileSize().width / 2) * 3, (11 + _tileMap->getTileSize().height / 2) * 3));
	}
	else if (Enemy3ShootPosition.x >= 115 * 3 && Enemy3ShootPosition.x <= 128 * 3 && Enemy3ShootPosition.y >= 11 * 3 && Enemy3ShootPosition.y <= 3 * 22)//���д�Ӫ GameOver
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
}

void GameScene::EnemyChecked4(float f)
{
	Size MyTankContent = MyTank->getContentSize();
	Rect MyTankRect = Rect(0, 0, MyTankContent.width, MyTankContent.height);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (Enemy4ShootPosition.x <= 5 || Enemy4ShootPosition.x >= visibleSize.width - 320 || Enemy4ShootPosition.y <= 5 || Enemy4ShootPosition.y >= visibleSize.height - 10)//������˱߽�
	{
		Enemy4ShootPosition = Enemy4->getPosition();
		Enemy4IsShooting = false;//ֹͣ���
		Enemy4AllowToShoot = true;//�����������
		if (IfEnemy4Bullet)
		{
			Enemybullet4->setPosition(0, 0);
			Enemybullet4->removeFromParent();//�ӵ�����
			IfEnemy4Bullet = false;
		}
	}
	else if (MyTankRect.containsPoint(MyTank->convertToNodeSpace(Enemy4ShootPosition)))//ע����Ҫת��Ϊģ������
	{//����������Ի�
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		Enemy4IsShooting = false;//ֹͣ���
		Enemy4AllowToShoot = true;//�����������
		if (IfEnemy4Bullet)
		{
			Enemybullet4->setPosition(0, 0);
			Enemybullet4->removeFromParent();//�ӵ�����
			IfEnemy4Bullet = false;
		}
		MyTank->setPosition(Vec2((11 + _tileMap->getTileSize().width / 2) * 3, (11 + _tileMap->getTileSize().height / 2) * 3));
	}
	else if (Enemy4ShootPosition.x >= 115 * 3 && Enemy4ShootPosition.x <= 128 * 3 && Enemy4ShootPosition.y >= 11 * 3 && Enemy4ShootPosition.y <= 3 * 22)//���д�Ӫ GameOver
	{
		IfScoreChanged = false;
		Scene * scene = GameOver::createScene();
		auto  layer = GameOver::create();
		layer->score = score;
		scene->addChild(layer);
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
	}
}

void GameScene::Shoot(float f)
{//����ú�����ÿ�ε��ù���������ӵ����飬��ɺ��Ƴ��ӵ�����
	Checked();//�����ӵ��ƶ�ǰ�ȼ��
	this->IfShoot(5);
	if (IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
		//ͬʱҪ���ж����������Ҫ����ֹ
	{
		switch (MyRotation)//����Ϊ�ϡ��ҡ��¡���
		{
		case 0:
		{
			ShootPosition.y +=3;
			bullet->setPosition(ShootPosition.x,ShootPosition.y);
		}; break;
		case 90:
		{
			ShootPosition.x += 3;
			bullet->setPosition(ShootPosition.x,ShootPosition.y);
		}break;
		case 180:
		{
			ShootPosition.y -= 3;
			bullet->setPosition(ShootPosition.x,ShootPosition.y);
		}break;
		case 270:
		{
			ShootPosition.x -= 3;
			bullet->setPosition(ShootPosition.x,ShootPosition.y);
		}break;
		default:break;
		}
	}
}

void GameScene::EnemyShoot1(float f)
{
	EnemyChecked1(0);//�����ӵ��ƶ�ǰ�ȼ��
	this->IfEnemy1Shoot(0);
	
	if (Enemy1IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
						   //ͬʱҪ���ж����������Ҫ����ֹ
	{
		switch (Enemy1Rotation)//����Ϊ�ϡ��ҡ��¡���
		{
		case 0:
		{
			Enemy1ShootPosition.y += 3;
			Enemybullet1->setPosition(Enemy1ShootPosition.x, Enemy1ShootPosition.y);
		}; break;
		case 90:
		{
			Enemy1ShootPosition.x += 3;
			Enemybullet1->setPosition(Enemy1ShootPosition.x, Enemy1ShootPosition.y);
		}break;
		case 180:
		{
			Enemy1ShootPosition.y -= 3;
			Enemybullet1->setPosition(Enemy1ShootPosition.x, Enemy1ShootPosition.y);
		}break;
		case 270:
		{
			Enemy1ShootPosition.x -= 3;
			Enemybullet1->setPosition(Enemy1ShootPosition.x, Enemy1ShootPosition.y);
		}break;
		default:break;
		}
	}
}

void GameScene::EnemyShoot2(float f)
{
	EnemyChecked2(0);//�����ӵ��ƶ�ǰ�ȼ��
	this->IfEnemy2Shoot(0);
	if (Enemy2IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
								 //ͬʱҪ���ж����������Ҫ����ֹ
	{
		switch (Enemy2Rotation)//����Ϊ�ϡ��ҡ��¡���
		{
		case 0:
		{
			Enemy2ShootPosition.y += 3;
			Enemybullet2->setPosition(Enemy2ShootPosition.x, Enemy2ShootPosition.y);
		}; break;
		case 90:
		{
			Enemy2ShootPosition.x += 3;
			Enemybullet2->setPosition(Enemy2ShootPosition.x, Enemy2ShootPosition.y);
		}break;
		case 180:
		{
			Enemy2ShootPosition.y -= 3;
			Enemybullet2->setPosition(Enemy2ShootPosition.x, Enemy2ShootPosition.y);
		}break;
		case 270:
		{
			Enemy2ShootPosition.x -= 3;
			Enemybullet2->setPosition(Enemy2ShootPosition.x, Enemy2ShootPosition.y);
		}break;
		default:break;
		}
	}
}

void GameScene::EnemyShoot3(float f)
{
	EnemyChecked3(0);//�����ӵ��ƶ�ǰ�ȼ��
	this->IfEnemy3Shoot(0);
	if (Enemy3IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
								 //ͬʱҪ���ж����������Ҫ����ֹ
	{
		switch (Enemy3Rotation)//����Ϊ�ϡ��ҡ��¡���
		{
		case 0:
		{
			Enemy3ShootPosition.y += 3;
			Enemybullet3->setPosition(Enemy3ShootPosition.x, Enemy3ShootPosition.y);
		}; break;
		case 90:
		{
			Enemy3ShootPosition.x += 3;
			Enemybullet3->setPosition(Enemy3ShootPosition.x, Enemy3ShootPosition.y);
		}break;
		case 180:
		{
			Enemy3ShootPosition.y -= 3;
			Enemybullet3->setPosition(Enemy3ShootPosition.x, Enemy3ShootPosition.y);
		}break;
		case 270:
		{
			Enemy3ShootPosition.x -= 3;
			Enemybullet3->setPosition(Enemy3ShootPosition.x, Enemy3ShootPosition.y);
		}break;
		default:break;
		}
	}
}

void GameScene::EnemyShoot4(float f)
{
	EnemyChecked4(0);//�����ӵ��ƶ�ǰ�ȼ��
	this->IfEnemy4Shoot(0);
	if (Enemy4IsShooting == true)//���״̬Ϊ����������Ͳ��������ӵ���ĳ������
								 //ͬʱҪ���ж����������Ҫ����ֹ
	{
		switch (Enemy4Rotation)//����Ϊ�ϡ��ҡ��¡���
		{
		case 0:
		{
			Enemy4ShootPosition.y += 3;
			Enemybullet4->setPosition(Enemy4ShootPosition.x, Enemy4ShootPosition.y);
		}; break;
		case 90:
		{
			Enemy4ShootPosition.x += 3;
			Enemybullet4->setPosition(Enemy4ShootPosition.x, Enemy4ShootPosition.y);
		}break;
		case 180:
		{
			Enemy4ShootPosition.y -= 3;
			Enemybullet4->setPosition(Enemy4ShootPosition.x, Enemy4ShootPosition.y);
		}break;
		case 270:
		{
			Enemy4ShootPosition.x -= 3;
			Enemybullet4->setPosition(Enemy4ShootPosition.x, Enemy4ShootPosition.y);
		}break;
		default:break;
		}
	}
}

Vec2 GameScene::PositionChanged()
{
	int offsetX = _tileMap->getTileSize().width * 3;//Xƫ����
	int offsetY = _tileMap->getTileSize().height * 3;//Yƫ����
	if (c == 'd')
	{
		MyTank->setRotation(90);
		return(Vec2(MyTank->getPosition().x + offsetX, MyTank->getPosition().y));
	}
	else if (c == 'a')
	{
		MyTank->setRotation(270);	
		return(Vec2(MyTank->getPosition().x - offsetX, MyTank->getPosition().y));
	}
	else if (c == 's')
	{
		MyTank->setRotation(180);
		return(Vec2(MyTank->getPosition().x, MyTank->getPosition().y - offsetY));
	}
	else if (c == 'w')
	{
		MyTank->setRotation(0);
		return(Vec2(MyTank->getPosition().x, MyTank->getPosition().y + offsetY));
	}
	else return Vec2(MyTank->getPosition().x, MyTank->getPosition().y);
}

void GameScene::IfShoot(float f)//����Ƿ�����ǽ��
{
	Vec2 tileCoord2 = this->tileCoordFromPosition((ShootPosition.x - _tileMap->getTileSize().width / 2) / 3, (ShootPosition.y - _tileMap->getTileSize().height / 2) / 3);
	int tileGid2 = _ShootLayer->getTileGIDAt(tileCoord2);
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propMap = prop.asValueMap();
		std::string shot = propMap["Shot"].asString();
		if (shot == "true")
		{
			IsShooting = false;//ֹͣ���
			AllowToShoot = true;//�����������
			if (IfBullet)
			{
				bullet->setPosition(0, 0);
				bullet->removeFromParent();//�ӵ�����
				IfBullet = false;
			}
			Layer1->removeTileAt(tileCoord2);
			_collidable->removeTileAt(tileCoord2);
			_ShootLayer->removeTileAt(tileCoord2);
		}
		else if (shot == "false")
		{
			IsShooting = false;//ֹͣ���
			AllowToShoot = true;//�����������
			if (IfBullet)
			{
				bullet->setPosition(0, 0);
				bullet->removeFromParent();//�ӵ�����
				IfBullet = false;
			}
		}
	}
}

void GameScene::IfEnemy1Shoot(float f)//����Ƿ�����ǽ��
{
	Vec2 tileCoord2 = this->tileCoordFromPosition((Enemy1ShootPosition.x - _tileMap->getTileSize().width / 2) / 3, (Enemy1ShootPosition.y - _tileMap->getTileSize().height / 2) / 3);
	int tileGid2 = _ShootLayer->getTileGIDAt(tileCoord2);
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propMap = prop.asValueMap();
		std::string shot = propMap["Shot"].asString();
		if (shot == "true")
		{
			Enemy1IsShooting = false;//ֹͣ���
			Enemy1AllowToShoot = true;//�����������
			if (IfEnemy1Bullet)
			{
				Enemybullet1->setPosition(0, 0);
				Enemybullet1->removeFromParent();//�ӵ�����
				IfEnemy1Bullet = false;
			}
			Layer1->removeTileAt(tileCoord2);
			_collidable->removeTileAt(tileCoord2);
			_ShootLayer->removeTileAt(tileCoord2);
		}
		else if (shot == "false")
		{
			Enemy1IsShooting = false;//ֹͣ���
			Enemy1AllowToShoot = true;//�����������
			if (IfEnemy1Bullet)
			{
				Enemybullet1->setPosition(0, 0);
				Enemybullet1->removeFromParent();//�ӵ�����
				IfEnemy1Bullet = false;
			}
		}
	}
}

void GameScene::IfEnemy2Shoot(float f)//����Ƿ�����ǽ��
{
	Vec2 tileCoord2 = this->tileCoordFromPosition((Enemy2ShootPosition.x - _tileMap->getTileSize().width / 2) / 3, (Enemy2ShootPosition.y - _tileMap->getTileSize().height / 2) / 3);
	int tileGid2 = _ShootLayer->getTileGIDAt(tileCoord2);
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propMap = prop.asValueMap();
		std::string shot = propMap["Shot"].asString();
		if (shot == "true")
		{
			Enemy2IsShooting = false;//ֹͣ���
			Enemy2AllowToShoot = true;//�����������
			if (IfEnemy2Bullet)
			{
				Enemybullet2->setPosition(0, 0);
				Enemybullet2->removeFromParent();//�ӵ�����
				IfEnemy2Bullet = false;
			}
			Layer1->removeTileAt(tileCoord2);
			_collidable->removeTileAt(tileCoord2);
			_ShootLayer->removeTileAt(tileCoord2);
		}
		else if (shot == "false")
		{
			Enemy2IsShooting = false;//ֹͣ���
			Enemy2AllowToShoot = true;//�����������
			if (IfEnemy2Bullet)
			{
				Enemybullet2->setPosition(0, 0);
				Enemybullet2->removeFromParent();//�ӵ�����
				IfEnemy2Bullet = false;
			}
		}
	}
}

void GameScene::IfEnemy3Shoot(float f)//����Ƿ�����ǽ��
{
	Vec2 tileCoord2 = this->tileCoordFromPosition((Enemy3ShootPosition.x - _tileMap->getTileSize().width / 2) / 3, (Enemy3ShootPosition.y - _tileMap->getTileSize().height / 2) / 3);
	int tileGid2 = _ShootLayer->getTileGIDAt(tileCoord2);
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propMap = prop.asValueMap();
		std::string shot = propMap["Shot"].asString();
		if (shot == "true")
		{
			Enemy3IsShooting = false;//ֹͣ���
			Enemy3AllowToShoot = true;//�����������
			if (IfEnemy3Bullet)
			{
				Enemybullet3->setPosition(0, 0);
				Enemybullet3->removeFromParent();//�ӵ�����
				IfEnemy3Bullet = false;
			}
			Layer1->removeTileAt(tileCoord2);
			_collidable->removeTileAt(tileCoord2);
			_ShootLayer->removeTileAt(tileCoord2);
		}
		else if (shot == "false")
		{
			Enemy3IsShooting = false;//ֹͣ���
			Enemy3AllowToShoot = true;//�����������
			if (IfEnemy3Bullet)
			{
				Enemybullet3->setPosition(0, 0);
				Enemybullet3->removeFromParent();//�ӵ�����
				IfEnemy3Bullet = false;
			}
		}
	}
}

void GameScene::IfEnemy4Shoot(float f)//����Ƿ�����ǽ��
{
	Vec2 tileCoord2 = this->tileCoordFromPosition((Enemy4ShootPosition.x - _tileMap->getTileSize().width / 2) / 3, (Enemy4ShootPosition.y - _tileMap->getTileSize().height / 2) / 3);
	int tileGid2 = _ShootLayer->getTileGIDAt(tileCoord2);
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propMap = prop.asValueMap();
		std::string shot = propMap["Shot"].asString();
		if (shot == "true")
		{
			Enemy4IsShooting = false;//ֹͣ���
			Enemy4AllowToShoot = true;//�����������
			if (IfEnemy4Bullet)
			{
				Enemybullet4->setPosition(0, 0);
				Enemybullet4->removeFromParent();//�ӵ�����
				IfEnemy4Bullet = false;
			}
			Layer1->removeTileAt(tileCoord2);
			_collidable->removeTileAt(tileCoord2);
			_ShootLayer->removeTileAt(tileCoord2);
		}
		else if (shot == "false")
		{
			Enemy4IsShooting = false;//ֹͣ���
			Enemy4AllowToShoot = true;//�����������
			if (IfEnemy4Bullet)
			{
				Enemybullet4->setPosition(0, 0);
				Enemybullet4->removeFromParent();//�ӵ�����
				IfEnemy4Bullet = false;
			}
		}
	}
}

void GameScene::Collidable(float f)
{
	MyPresentPoint = PositionChanged();
	Vec2 tileCoord = this->tileCoordFromPosition((MyPresentPoint.x - _tileMap->getTileSize().width / 2) / 3, (MyPresentPoint.y - _tileMap->getTileSize().height / 2) / 3); //ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ö�Ӧ��Ƭ�������Ƭ��GIDֵ�������б���Ƭ�Ƿ����

	if (tileGid > 0)
	{//tileGid��ֵΪ0ʱ��Ƭ������
		Value prop = _tileMap->getPropertiesForGID(tileGid);//ͨ����Ӧ��Ƭ��GIDֵ��ȡ��Ƭ�����Լ��ϣ�ÿ��GID��Ӧ��ͬ������Ƭ��
		ValueMap propValueMap = prop.asValueMap();//�����Լ���ת��Ϊmap����
		std::string collision = propValueMap["Collidable"].asString(); //��"Collidale"���Զ�Ӧֵת��Ϊ�ַ�����ʽ
		if (collision == "true") //��ײ���ɹ�
		{
			return;
		}
	}
	else if (MyPresentPoint == EnemyPresentPoint1 || MyPresentPoint == EnemyPresentPoint2||MyPresentPoint == EnemyPresentPoint3 ||MyPresentPoint==EnemyPresentPoint4)
	{//���ײ���˵��ˣ��������Ի�λ��
		--remainlife;
		this->removeChild(LifeLabel);

		if (remainlife == 0)
		{
			IfScoreChanged = false;
			Scene * scene = GameOver::createScene();
			auto  layer = GameOver::create();
			layer->score = score;
			scene->addChild(layer);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
		}

		Value LifeValue1(remainlife);
		std::string LifeText1 = LifeValue1.asString();//����ת��Ϊ�ַ���
		LifeLabel = Label::createWithBMFont("futura-48.fnt", LifeText1);
		LifeLabel->setPosition(800, 450);
		LifeLabel->setScale(0.7);
		this->addChild(LifeLabel);

		SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		MyTank->setPosition(Vec2((11 + _tileMap->getTileSize().width / 2) * 3, (11 + _tileMap->getTileSize().height / 2) * 3));
		return;
	}
	//�����Ӧ���ƶ���ҵ�λ��

	Move(5);
}
void GameScene::EnemyCollidable1(float f)
{
	EnemyPositionChanged1(0);
	Vec2 tileCoord = this->tileCoordFromPosition((EnemyPresentPoint1.x-_tileMap->getTileSize().width/2)/3, (EnemyPresentPoint1.y- _tileMap->getTileSize().height / 2) / 3); //ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ö�Ӧ��Ƭ�������Ƭ��GIDֵ�������б���Ƭ�Ƿ����

	if (tileGid > 0)
	{//tileGid��ֵΪ0ʱ��Ƭ������
		Value prop = _tileMap->getPropertiesForGID(tileGid);//ͨ����Ӧ��Ƭ��GIDֵ��ȡ��Ƭ�����Լ��ϣ�ÿ��GID��Ӧ��ͬ������Ƭ��
		ValueMap propValueMap = prop.asValueMap();//�����Լ���ת��Ϊmap����
		std::string collision = propValueMap["Collidable"].asString(); //��"Collidale"���Զ�Ӧֵת��Ϊ�ַ�����ʽ
		if (collision == "true") //��ײ���ɹ�
		{
			return;
		}
	}
	EnemyMove1(0);
}

void GameScene::EnemyCollidable2(float f)
{
	EnemyPositionChanged2(0);
	Vec2 tileCoord = this->tileCoordFromPosition((EnemyPresentPoint2.x - _tileMap->getTileSize().width / 2) / 3, (EnemyPresentPoint2.y - _tileMap->getTileSize().height / 2) / 3); //ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ö�Ӧ��Ƭ�������Ƭ��GIDֵ�������б���Ƭ�Ƿ����

	if (tileGid > 0)
	{//tileGid��ֵΪ0ʱ��Ƭ������
		Value prop = _tileMap->getPropertiesForGID(tileGid);//ͨ����Ӧ��Ƭ��GIDֵ��ȡ��Ƭ�����Լ��ϣ�ÿ��GID��Ӧ��ͬ������Ƭ��
		ValueMap propValueMap = prop.asValueMap();//�����Լ���ת��Ϊmap����
		std::string collision = propValueMap["Collidable"].asString(); //��"Collidale"���Զ�Ӧֵת��Ϊ�ַ�����ʽ
		if (collision == "true") //��ײ���ɹ�
		{
			return;
		}
	}
	EnemyMove2(0);
}

void GameScene::EnemyCollidable3(float f)
{
	EnemyPositionChanged3(0);
	Vec2 tileCoord = this->tileCoordFromPosition((EnemyPresentPoint3.x - _tileMap->getTileSize().width / 2) / 3, (EnemyPresentPoint3.y - _tileMap->getTileSize().height / 2) / 3); //ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ö�Ӧ��Ƭ�������Ƭ��GIDֵ�������б���Ƭ�Ƿ����

	if (tileGid > 0)
	{//tileGid��ֵΪ0ʱ��Ƭ������
		Value prop = _tileMap->getPropertiesForGID(tileGid);//ͨ����Ӧ��Ƭ��GIDֵ��ȡ��Ƭ�����Լ��ϣ�ÿ��GID��Ӧ��ͬ������Ƭ��
		ValueMap propValueMap = prop.asValueMap();//�����Լ���ת��Ϊmap����
		std::string collision = propValueMap["Collidable"].asString(); //��"Collidale"���Զ�Ӧֵת��Ϊ�ַ�����ʽ
		if (collision == "true") //��ײ���ɹ�
		{
			return;
		}
	}
	EnemyMove3(0);
}

void GameScene::EnemyCollidable4(float f)
{
	EnemyPositionChanged4(0);
	Vec2 tileCoord = this->tileCoordFromPosition((EnemyPresentPoint4.x - _tileMap->getTileSize().width / 2) / 3, (EnemyPresentPoint4.y - _tileMap->getTileSize().height / 2) / 3); //ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ö�Ӧ��Ƭ�������Ƭ��GIDֵ�������б���Ƭ�Ƿ����

	if (tileGid > 0)
	{//tileGid��ֵΪ0ʱ��Ƭ������
		Value prop = _tileMap->getPropertiesForGID(tileGid);//ͨ����Ӧ��Ƭ��GIDֵ��ȡ��Ƭ�����Լ��ϣ�ÿ��GID��Ӧ��ͬ������Ƭ��
		ValueMap propValueMap = prop.asValueMap();//�����Լ���ת��Ϊmap����
		std::string collision = propValueMap["Collidable"].asString(); //��"Collidale"���Զ�Ӧֵת��Ϊ�ַ�����ʽ
		if (collision == "true") //��ײ���ɹ�
		{
			return;
		}
	}
	EnemyMove4(0);
}

void GameScene::EnemyPositionChanged1(float f)//�����ƶ��ĺ���
{
	auto TileSize = _tileMap->getTileSize()*3;
	EnemyPresentPoint1 = Enemy1->getPosition();
	int MovePos1 = CCRANDOM_0_1() * 1000;
	if (MovePos1 >= 0 && MovePos1 <= 100)
	{
		Enemy1->setRotation(0);
		EnemyPresentPoint1.y += TileSize.height;
	}
	else if (MovePos1 > 100 && MovePos1 <= 200)
	{
		Enemy1->setRotation(180);
		EnemyPresentPoint1.y -= TileSize.height;
	}
	else if (MovePos1 > 200 && MovePos1 <= 300)
	{
		Enemy1->setRotation(90);
		EnemyPresentPoint1.x += TileSize.width;
	}
	else if (MovePos1 >300 && MovePos1 <= 400)
	{
		Enemy1->setRotation(270);
		EnemyPresentPoint1.x -= TileSize.width;
	}
	else if (MovePos1 > 600 && MovePos1 <= 1000)
	{//���
		if (Enemy1AllowToShoot)
		{
			Enemy1IsShooting = true;
			Enemy1AllowToShoot = false;
			Enemy1Rotation = Enemy1->getRotation();//��õ���1̹�˵ĽǶ�
			Enemy1ShootPosition = Enemy1->getPosition();//�����ӵ�Ҫ��̹�����￪ʼ�ƶ�
			Enemybullet1->setPosition(0, 0);
			this->addChild(Enemybullet1);
			IfEnemy1Bullet = true;
		}
	}
}

void GameScene::EnemyPositionChanged2(float f)//�����ƶ��ĺ���
{
	auto TileSize = _tileMap->getTileSize() * 3;
	EnemyPresentPoint2 = Enemy2->getPosition();
	int MovePos1 = CCRANDOM_0_1() * 1000;
	if (MovePos1 >= 0 && MovePos1 <= 100)
	{
		Enemy2->setRotation(0);
		EnemyPresentPoint2.y += TileSize.height;
	}
	else if (MovePos1 > 100 && MovePos1 <= 200)
	{
		Enemy2->setRotation(180);
		EnemyPresentPoint2.y -= TileSize.height;
	}
	else if (MovePos1 > 200 && MovePos1 <= 300)
	{
		Enemy2->setRotation(90);
		EnemyPresentPoint2.x += TileSize.width;
	}
	else if (MovePos1 >300 && MovePos1 <= 400)
	{
		Enemy2->setRotation(270);
		EnemyPresentPoint2.x -= TileSize.width;
	}
	else if (MovePos1 > 600 && MovePos1 <= 1000)
	{//���
		if (Enemy2AllowToShoot)
		{
			Enemy2IsShooting = true;
			Enemy2AllowToShoot = false;
			Enemy2Rotation = Enemy2->getRotation();//��õ���1̹�˵ĽǶ�
			Enemy2ShootPosition = Enemy2->getPosition();//�����ӵ�Ҫ��̹�����￪ʼ�ƶ�
			Enemybullet2->setPosition(0, 0);
			this->addChild(Enemybullet2);
			IfEnemy2Bullet = true;
		}
	}
}

void GameScene::EnemyPositionChanged3(float f)//�����ƶ��ĺ���
{
	auto TileSize = _tileMap->getTileSize() * 3;
	EnemyPresentPoint3 = Enemy3->getPosition();
	int MovePos1 = CCRANDOM_0_1() * 1000;
	if (MovePos1 >= 0 && MovePos1 <= 100)
	{
		Enemy3->setRotation(0);
		EnemyPresentPoint3.y += TileSize.height;
	}
	else if (MovePos1 > 100 && MovePos1 <= 200)
	{
		Enemy3->setRotation(180);
		EnemyPresentPoint3.y -= TileSize.height;
	}
	else if (MovePos1 > 200 && MovePos1 <= 300)
	{
		Enemy3->setRotation(90);
		EnemyPresentPoint3.x += TileSize.width;
	}
	else if (MovePos1 >300 && MovePos1 <= 400)
	{
		Enemy3->setRotation(270);
		EnemyPresentPoint3.x -= TileSize.width;
	}
	else if (MovePos1 > 600 && MovePos1 <= 1000)
	{//���
		if (Enemy3AllowToShoot)
		{
			Enemy3IsShooting = true;
			Enemy3AllowToShoot = false;
			Enemy3Rotation = Enemy3->getRotation();//��õ���1̹�˵ĽǶ�
			Enemy3ShootPosition = Enemy3->getPosition();//�����ӵ�Ҫ��̹�����￪ʼ�ƶ�
			Enemybullet3->setPosition(0, 0);
			this->addChild(Enemybullet3);
			IfEnemy3Bullet = true;
		}
	}
}

void GameScene::EnemyPositionChanged4(float f)//�����ƶ��ĺ���
{
	auto TileSize = _tileMap->getTileSize() * 3;
	EnemyPresentPoint4 = Enemy4->getPosition();
	int MovePos1 = CCRANDOM_0_1() * 1000;
	if (MovePos1 >= 0 && MovePos1 <= 100)
	{
		Enemy4->setRotation(0);
		EnemyPresentPoint4.y += TileSize.height;
	}
	else if (MovePos1 > 100 && MovePos1 <= 200)
	{
		Enemy4->setRotation(180);
		EnemyPresentPoint4.y -= TileSize.height;
	}
	else if (MovePos1 > 200 && MovePos1 <= 300)
	{
		Enemy4->setRotation(90);
		EnemyPresentPoint4.x += TileSize.width;
	}
	else if (MovePos1 >300 && MovePos1 <= 400)
	{
		Enemy4->setRotation(270);
		EnemyPresentPoint4.x -= TileSize.width;
	}
	else if (MovePos1 > 600 && MovePos1 <= 1000)
	{//���
		if (Enemy4AllowToShoot)
		{
			Enemy4IsShooting = true;
			Enemy4AllowToShoot = false;
			Enemy4Rotation = Enemy4->getRotation();//��õ���1̹�˵ĽǶ�
			Enemy4ShootPosition = Enemy4->getPosition();//�����ӵ�Ҫ��̹�����￪ʼ�ƶ�
			Enemybullet1->setPosition(0, 0);
			this->addChild(Enemybullet4);
			IfEnemy4Bullet = true;
		}
	}
}

void GameScene::EnemyMove1(float f)
{
	Enemy1->setPosition(EnemyPresentPoint1);
}

void GameScene::EnemyMove2(float f)
{
	Enemy2->setPosition(EnemyPresentPoint2);
}

void GameScene::EnemyMove3(float f)
{
	Enemy3->setPosition(EnemyPresentPoint3);
}

void GameScene::EnemyMove4(float f)
{
	Enemy4->setPosition(EnemyPresentPoint4);
}

void GameScene::Move(float f)
{
	Vec2 MyPresent = MyPresentPoint;

	if (c == 'd'&&Ismoving == true)
	{
		MyTank->setPosition(MyPresent);
	}
	else if (c == 'a'&&Ismoving == true)
	{
		MyTank->setPosition(MyPresent);
	}
	else if (c == 's'&&Ismoving == true)
	{
		MyTank->setPosition(MyPresent);
	}
	else if (c == 'w'&&Ismoving == true)
	{
		MyTank->setPosition(MyPresent);
	}
}

Vec2  GameScene::tileCoordFromPosition(float x0,float y0)
{
	int x = x0 / _tileMap->getTileSize().width;
	int y = (_tileMap->getTileSize().height*_tileMap->getMapSize().height - y0) / _tileMap->getTileSize().height;
	return Vec2(x, y);//�����Ƭ��Ӧ����Ƭ����
}

Vec2 GameScene::PositionFromtileCoord(float x0, float y0)//��Ƭ���귵��Ϊԭ����
{
	int x = x0*_tileMap->getTileSize().width;
	int y = _tileMap->getTileSize().height*_tileMap->getMapSize().height - y0*_tileMap->getTileSize().height;
	return Vec2(x, y);
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
			MyRotation = MyTank->getRotation();//����Լ�̹�˵ĽǶ�
			ShootPosition = MyTank->getPosition();//�����ӵ�Ҫ��̹�����￪ʼ�ƶ�
			bullet->setPosition(0, 0);
			this->addChild(bullet);
			IfBullet = true;
			SimpleAudioEngine::getInstance()->playEffect("Shoot.wav");
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
	if (keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_S || keycode == EventKeyboard::KeyCode::KEY_A)
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
					it = vc.erase(it);
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
		case EventKeyboard::KeyCode::KEY_S: {c = 's';if (!IfPause) { c0 = 'm'; } else { c0 = ' '; }}break;
		case EventKeyboard::KeyCode::KEY_A: {c = 'a'; if (!IfPause) { c0 = 'm'; } else { c0 = ' ';  }} break;
		case EventKeyboard::KeyCode::KEY_J: { if (!IfPause) { c0 = 'm'; } else { c0 = ' '; } }; break;
		}
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

	Size vsize = Director::getInstance()->getVisibleSize();
	Vec2 Ori = Director::getInstance()->getVisibleOrigin();

	this->schedule(schedule_selector(GameScene::Collidable), 0.2);
	this->schedule(schedule_selector(GameScene::Shoot), 0.012);//����ִ���ƶ����������
	this->schedule(schedule_selector(GameScene::EnemyCollidable1), 0.2);
	this->schedule(schedule_selector(GameScene::EnemyShoot1), 0.012);
	this->schedule(schedule_selector(GameScene::EnemyCollidable2), 0.2);
	this->schedule(schedule_selector(GameScene::EnemyShoot2), 0.012);
	this->schedule(schedule_selector(GameScene::EnemyCollidable3), 0.2);
	this->schedule(schedule_selector(GameScene::EnemyShoot3), 0.012);
	this->schedule(schedule_selector(GameScene::EnemyCollidable4), 0.2);
	this->schedule(schedule_selector(GameScene::EnemyShoot4), 0.012);

	if (score >= 0 && score < 2500)
		_tileMap = TMXTiledMap::create("TankMap2.tmx");
	else if (score >= 2500 & score <6000)
	{
		_tileMap = TMXTiledMap::create("TankMap1.tmx");
	}
	else if (score >= 6000 && score < 10000)
	{
		_tileMap = TMXTiledMap::create("TankMap3.tmx");
	}
	_tileMap->setScale(3);
	_tileMap->setPosition(Ori.x, Ori.y );
	addChild(_tileMap, 0, 100);//��̹�˴�ս��ͼ��ӽ�ȥ

	_collidable = _tileMap->getLayer("Collidable");//��ײ����
	Layer1 = _tileMap->getLayer("Layer1");//��ͼͼ��
	_ShootLayer = _tileMap->getLayer("Shoot");//�������

	TMXObjectGroup *group = _tileMap->getObjectGroup("Objects");//����Լ�̹�˺͵л�̹�˵Ķ�����

	ValueMap MyTankPoint = group->getObject("MyTank");
	Vec2 MyPoint;
	MyPoint.x = (MyTankPoint["x"].asFloat()+_tileMap->getTileSize().width/2)*3;
	MyPoint.y = (MyTankPoint["y"].asFloat()+_tileMap->getTileSize().height/2)*3;//����Լ�̹������
	MyTank = Sprite::create("Tank.png");
	MyTank->setScale(3);

	MyTank->setPosition(MyPoint);
	this->addChild(MyTank);

	ValueMap EnemyTankPoint1 = group->getObject("Enemy1");
	Vec2 EnemyPoint1;
	EnemyPoint1.x = (EnemyTankPoint1["x"].asFloat() + _tileMap->getTileSize().width / 2)*3;
	EnemyPoint1.y = (EnemyTankPoint1["y"].asFloat() + _tileMap->getTileSize().height / 2)*3;
	Enemy1 = Sprite::create("enemyTank.png");
	Enemy1->setScale(3);
	Enemy1->setPosition(EnemyPoint1);
	this->addChild(Enemy1);

	ValueMap EnemyTankPoint2 = group->getObject("Enemy2");
	Vec2 EnemyPoint2;
	EnemyPoint2.x = (EnemyTankPoint2["x"].asFloat()+ _tileMap->getTileSize().width / 2)*3;
	EnemyPoint2.y = (EnemyTankPoint2["y"].asFloat() + _tileMap->getTileSize().height / 2)*3;
	Enemy2 = Sprite::create("enemyTank.png");
	Enemy2->setScale(3);
	Enemy2->setPosition(EnemyPoint2);
	this->addChild(Enemy2);

	ValueMap EnemyTankPoint3 = group->getObject("Enemy3");
	Vec2 EnemyPoint3;
	EnemyPoint3.x = (EnemyTankPoint3["x"].asFloat()+ _tileMap->getTileSize().width / 2)*3;
	EnemyPoint3.y = (EnemyTankPoint3["y"].asFloat() + _tileMap->getTileSize().height/ 2)*3;
	Enemy3 = Sprite::create("enemyTank.png");
	Enemy3->setScale(3);
	Enemy3->setPosition(EnemyPoint3);
	this->addChild(Enemy3);

	ValueMap EnemyTankPoint4 = group->getObject("Enemy4");
	Vec2 EnemyPoint4;
	EnemyPoint4.x = (EnemyTankPoint4["x"].asFloat() + _tileMap->getTileSize().width / 2)*3;
	EnemyPoint4.y = (EnemyTankPoint4["y"].asFloat() + _tileMap->getTileSize().height / 2)*3;
	Enemy4 = Sprite::create("enemyTank.png");
	Enemy4->setScale(3);
	Enemy4->setPosition(EnemyPoint4);
	this->addChild(Enemy4);

	bullet = Sprite::create("smallbullet.png");//�����ӵ�����
	bullet->setPosition(0, 0);
	this->addChild(bullet);

	Enemybullet1 = Sprite::create("smallbullet.png");
	Enemybullet1->setPosition(0, 0);
	this->addChild(Enemybullet1);

	Enemybullet2 = Sprite::create("smallbullet.png");
	Enemybullet2->setPosition(0, 0);
	this->addChild(Enemybullet2);

	Enemybullet3 = Sprite::create("smallbullet.png");
	Enemybullet3->setPosition(0, 0);
	this->addChild(Enemybullet3);

	Enemybullet4 = Sprite::create("smallbullet.png");
	Enemybullet4->setPosition(0, 0);
	this->addChild(Enemybullet4);
	
	auto menu = Menu::create();
	this->addChild(menu);
	auto Back = MenuItemLabel::create(Label::createWithBMFont("futura-48.fnt", "Back to main menu"), CC_CALLBACK_1(GameScene::BackToMenu, this));
	Back->setPosition(Ori.x + 300, Ori.y + 250);
	Back->setScale(0.7);
	menu->addChild(Back);

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

	return true;
}

void GameScene::onEnterTransitionDidFinish()
{//���ű������֣���ʼ������ʱ�����������ɼ�����ע��
	Layer::onEnterTransitionDidFinish();

	SimpleAudioEngine::getInstance()->playEffect("111.wav");//������Ч

	auto listener = EventListenerKeyboard::create();//�������̼�����

	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed,this);//���̰���ʱ���ƶ�
	listener->onKeyReleased =CC_CALLBACK_2(GameScene::onKeyReleased,this);//�����ɿ�ʱ�Ĳ���

	auto eventdispatcher = Director::getInstance()->getEventDispatcher();
	eventdispatcher->addEventListenerWithSceneGraphPriority(listener, MyTank);
}

void GameScene::onExit()
{
	Layer::onExit();
	if(!IfScoreChanged)
		score = 0;//����
	remainlife = 3;//������

	IfPause = false;//�Ƿ���ͣ
	c = ' ';//���Ƽ���
	c0 = 'm';//������ͣ
	count0 = 0;//���ü���
	Ismoving = false;//�Ƿ����ƶ�

	MyPresentPoint = Vec2(18.0f, 54.0f);
	IsShooting = false;//�Ƿ������
	AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	MyRotation = 0;//�Լ��ĽǶȣ����ڸ������
	ShootPosition = Vec2(110, 110);//�ӵ�������
	IfBullet = false;//�Ƿ�����ӵ�

	EnemyPresentPoint1 = Vec2((44 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy1ShootPosition = Vec2(110, 44);//����1���ӵ�����
	IfEnemy1Bullet = false;//�Ƿ���ڵ���1���ӵ�
	Enemy1IsShooting = false;//�Ƿ������
	Enemy1AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy1Rotation = 0;//�л�1�ĽǶ�

	EnemyPresentPoint2 = Vec2((110 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy2ShootPosition = Vec2(110, 44);//����2���ӵ�����
	IfEnemy2Bullet = false;//�Ƿ���ڵ���2���ӵ�
	Enemy2IsShooting = false;//�Ƿ������
	Enemy2AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy2Rotation = 0;//�л�2�ĽǶ�

	EnemyPresentPoint3 = Vec2((176 + 11 / 2) * 3, (44 + 11 / 2) * 3);
	Enemy3ShootPosition = Vec2(110, 44);//����3���ӵ�����
	IfEnemy3Bullet = false;//�Ƿ���ڵ���3���ӵ�
	Enemy3IsShooting = false;//�Ƿ������
	Enemy3AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy3Rotation = 0;//�л�3�ĽǶ�

	EnemyPresentPoint4 = Vec2((110 + 11 / 2) * 3, (110 + 11 / 2) * 3);
	Enemy4ShootPosition = Vec2(110, 44);//����4���ӵ�����
	IfEnemy4Bullet = false;//�Ƿ���ڵ���4���ӵ�
	Enemy4IsShooting = false;//�Ƿ������
	Enemy4AllowToShoot = true;//�Ƿ����������һ��ֻ����һ���ӵ�
	Enemy4Rotation = 0;//�л�4�ĽǶ�

}