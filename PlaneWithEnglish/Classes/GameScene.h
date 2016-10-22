#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include<vector>
#include"HelloWorldScene.h"

using namespace std;
USING_NS_CC;

using namespace cocostudio::timeline;


class GameScene : public cocos2d::Layer//������������
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene(){};//��������

	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	void Move(float f);//�����Ի��ƶ�
	void Checked();//�����ӵ���ײ
	void Shoot(float f);//�����ӵ����

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pevent);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pevent);

	void BackToMenu(Ref* ref);//�������˵�

	//��Ļ����ֻ����������л�
	void EnemyAppearingFromTop(float f);//��ʱִ���µл����ɵĺ���
	void EnemyMove(float f);//�л��ƶ�

	void ScoreChecked();//�������

private:
	Sprite* _MyPlane;//���
	Sprite* _Bullet;//�ӵ�
	Label * ScoreLabel;//�������� 
	Label * LifeLabel;//ʣ������������
	Sprite * _Enemy;//�л�
	Sprite * _Enemy1;//�л�
	Sprite * _Enemy2;//�л�
	Sprite * _Enemy3;//�л�
	Label * WordNow;
};

class myPlane {//�Ի�������
public:
	~myPlane() { };//��������
	myPlane(const myPlane &rhs)//�������캯��
	{
		MyPoint = rhs.MyPoint;
		PlanePicture = rhs.PlanePicture;
		MyPlaneTag = rhs.MyPlaneTag;
	}

	myPlane operator=(const myPlane &rhs)
	{
		MyPoint = rhs.MyPoint;
		PlanePicture = rhs.PlanePicture;
		MyPlaneTag = rhs.MyPlaneTag;
		return *this;
	}
	//���˿������캯�����붨��Ĭ�Ϲ��캯��������Ĭ�Ϲ��캯��������
	myPlane() = default;

	int getMyPlaneTag() { return MyPlaneTag; };
	Vec2 getMyPlanePoint() { return MyPoint; };
	std::string getPlanePicture() { return PlanePicture; };

private:
	Vec2 MyPoint = Vec2(480, 120);//������Ϣ
	std::string PlanePicture=std::string("plane.png");//���ͼƬ�ļ���
	int MyPlaneTag = 100;//��Ҷ�Ӧ��ǩ

};

class bullet {
public:
	~bullet() {};//��������
	bullet(const bullet &rhs)
	{
		BulletPoint = rhs.BulletPoint;
		BulletPicture = rhs.BulletPicture;
		BulletTag = rhs.BulletTag;
	}
	bullet& operator=(const bullet& rhs)
	{
		BulletPoint = rhs.BulletPoint;
		BulletPicture = rhs.BulletPicture;
		BulletTag = rhs.BulletTag;
	}
	bullet() = default;

	int getBulletTag() { return BulletTag; };
	Vec2 getBulletPoint() { return BulletPoint; };
	std::string getBulletPicture() { return BulletPicture; };

private:
	Vec2 BulletPoint = Vec2(0, 0);//�ӵ�������Ϣ
	std::string BulletPicture = std::string("smallbullet.png");//�ӵ�ͼƬ�ļ���
	int BulletTag = 200;//�ӵ���Ӧ��ǩ

};


#endif 
