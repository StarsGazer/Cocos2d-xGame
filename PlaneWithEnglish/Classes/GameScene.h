#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include<vector>
#include"HelloWorldScene.h"

using namespace std;
USING_NS_CC;

using namespace cocostudio::timeline;


class GameScene : public cocos2d::Layer//包含析构函数
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene(){};//析构函数

	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	void Move(float f);//处理自机移动
	void Checked();//处理子弹碰撞
	void Shoot(float f);//处理子弹射击

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pevent);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pevent);

	void BackToMenu(Ref* ref);//返回主菜单

	//屏幕里面只允许有五个敌机
	void EnemyAppearingFromTop(float f);//定时执行新敌机生成的函数
	void EnemyMove(float f);//敌机移动

	void ScoreChecked();//分数检查

private:
	Sprite* _MyPlane;//玩家
	Sprite* _Bullet;//子弹
	Label * ScoreLabel;//分数计算 
	Label * LifeLabel;//剩余生命数计算
	Sprite * _Enemy;//敌机
	Sprite * _Enemy1;//敌机
	Sprite * _Enemy2;//敌机
	Sprite * _Enemy3;//敌机
	Label * WordNow;
};

class myPlane {//自机操作类
public:
	~myPlane() { };//析构函数
	myPlane(const myPlane &rhs)//拷贝构造函数
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
	//有了拷贝构造函数必须定义默认构造函数，否则默认构造函数不存在
	myPlane() = default;

	int getMyPlaneTag() { return MyPlaneTag; };
	Vec2 getMyPlanePoint() { return MyPoint; };
	std::string getPlanePicture() { return PlanePicture; };

private:
	Vec2 MyPoint = Vec2(480, 120);//坐标信息
	std::string PlanePicture=std::string("plane.png");//玩家图片文件名
	int MyPlaneTag = 100;//玩家对应标签

};

class bullet {
public:
	~bullet() {};//析构函数
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
	Vec2 BulletPoint = Vec2(0, 0);//子弹坐标信息
	std::string BulletPicture = std::string("smallbullet.png");//子弹图片文件名
	int BulletTag = 200;//子弹对应标签

};


#endif 
