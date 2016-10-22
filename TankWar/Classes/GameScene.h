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

	void Move(float f);//�����ƶ�

	void EnemyMove1(float f);//�����ƶ�
	void EnemyPositionChanged1(float f);//���˵�λ�øı�
	void EnemyMove2(float f);//�����ƶ�
	void EnemyPositionChanged2(float f);//���˵�λ�øı�
	void EnemyMove3(float f);//�����ƶ�
	void EnemyPositionChanged3(float f);//���˵�λ�øı�
	void EnemyMove4(float f);//�����ƶ�
	void EnemyPositionChanged4(float f);//���˵�λ�øı�

	Vec2 tileCoordFromPosition(float x0,float y0);//ת��Ϊ��Ƭ����
	Vec2 PositionFromtileCoord(float x0, float yo);//��Ƭ���귴תΪԭ����

	void Collidable(float f);//�����ײ
	void EnemyCollidable1(float f);//�����˵���ײ
	void EnemyCollidable2(float f);//�����˵���ײ
	void EnemyCollidable3(float f);//�����˵���ײ
	void EnemyCollidable4(float f);//�����˵���ײ

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pevent);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *pevent);

	Vec2 PositionChanged();//���ظı��λ��

	void Shoot(float f);//����ú���
	void Checked();//����ӵ���״̬�������Ƿ�������
	void IfShoot(float f);//����Ƿ�����ǽ��

	void EnemyShoot1(float f);//����1�������
	void EnemyChecked1(float f);//����1���������Χ�ļ�⺯��
	void IfEnemy1Shoot(float f);//����Ƿ�����ǽ��
	void EnemyShoot2(float f);//����1�������
	void EnemyChecked2(float f);//����1���������Χ�ļ�⺯��
	void IfEnemy2Shoot(float f);//����Ƿ�����ǽ��
	void EnemyShoot3(float f);//����1�������
	void EnemyChecked3(float f);//����1���������Χ�ļ�⺯��
	void IfEnemy3Shoot(float f);//����Ƿ�����ǽ��
	void EnemyShoot4(float f);//����1�������
	void EnemyChecked4(float f);//����1���������Χ�ļ�⺯��
	void IfEnemy4Shoot(float f);//����Ƿ�����ǽ��

	void ScoreChecked();//�������

private:
	Sprite* MyTank;//�Ի�
	TMXTiledMap * _tileMap;//��Ƭ��ͼ
	Sprite* Enemy1;//�л�
	Sprite* Enemy2;
	Sprite* Enemy3;
	Sprite* Enemy4;
	TMXLayer *_collidable;//������Ƭ��ͼ�Ĳ����
	Sprite * bullet;//�ӵ�
	TMXLayer * Layer1;//ͼ�㣬����������Ƭ
	TMXLayer * _ShootLayer;//�������Ĳ�
	Sprite *Enemybullet1;//����1���ӵ�
	Sprite *Enemybullet2;//����2�ĵ�
	Sprite *Enemybullet3;//����3���ӵ�
	Sprite *Enemybullet4;//����4���ӵ�
	Label * ScoreLabel;//�������� 
	Label * LifeLabel;//ʣ������������
};

#endif // __HELLOWORLD_SCENE_H__
