#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

private:
	virtual bool init();

	// implement the "static create()" method manually
public:
	CREATE_FUNC(GameScene);

	void BackToMenu(Ref *ref);

	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	void Move(float f);//键盘移动

	void EnemyMove1(float f);//敌人移动
	void EnemyPositionChanged1(float f);//敌人的位置改变
	void EnemyMove2(float f);//敌人移动
	void EnemyPositionChanged2(float f);//敌人的位置改变
	void EnemyMove3(float f);//敌人移动
	void EnemyPositionChanged3(float f);//敌人的位置改变
	void EnemyMove4(float f);//敌人移动
	void EnemyPositionChanged4(float f);//敌人的位置改变

	Vec2 tileCoordFromPosition(float x0,float y0);//转化为瓦片坐标
	Vec2 PositionFromtileCoord(float x0, float yo);//瓦片坐标反转为原坐标

	void Collidable(float f);//检测碰撞
	void EnemyCollidable1(float f);//检测敌人的碰撞
	void EnemyCollidable2(float f);//检测敌人的碰撞
	void EnemyCollidable3(float f);//检测敌人的碰撞
	void EnemyCollidable4(float f);//检测敌人的碰撞

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pevent);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *pevent);

	Vec2 PositionChanged();//返回改变的位置

	void Shoot(float f);//射击用函数
	void Checked();//监控子弹的状态，决定是否继续射击
	void IfShoot(float f);//检测是否射中墙壁

	void EnemyShoot1(float f);//敌人1射击函数
	void EnemyChecked1(float f);//敌人1射击超出范围的检测函数
	void IfEnemy1Shoot(float f);//检测是否射中墙壁
	void EnemyShoot2(float f);//敌人1射击函数
	void EnemyChecked2(float f);//敌人1射击超出范围的检测函数
	void IfEnemy2Shoot(float f);//检测是否射中墙壁
	void EnemyShoot3(float f);//敌人1射击函数
	void EnemyChecked3(float f);//敌人1射击超出范围的检测函数
	void IfEnemy3Shoot(float f);//检测是否射中墙壁
	void EnemyShoot4(float f);//敌人1射击函数
	void EnemyChecked4(float f);//敌人1射击超出范围的检测函数
	void IfEnemy4Shoot(float f);//检测是否射中墙壁

	void ScoreChecked();//分数检查

private:
	Sprite* MyTank;//自机
	TMXTiledMap * _tileMap;//瓦片地图
	Sprite* Enemy1;//敌机
	Sprite* Enemy2;
	Sprite* Enemy3;
	Sprite* Enemy4;
	TMXLayer *_collidable;//创建瓦片地图的层对象
	Sprite * bullet;//子弹
	TMXLayer * Layer1;//图层，用于消除瓦片
	TMXLayer * _ShootLayer;//检测射击的层
	Sprite *Enemybullet1;//敌人1的子弹
	Sprite *Enemybullet2;//敌人2的弹
	Sprite *Enemybullet3;//敌人3的子弹
	Sprite *Enemybullet4;//敌人4的子弹
	Label * ScoreLabel;//分数计算 
	Label * LifeLabel;//剩余生命数计算
};

#endif // __HELLOWORLD_SCENE_H__
