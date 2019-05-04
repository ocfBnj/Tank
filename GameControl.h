#pragma once

#include <graphics.h>
#include <memory>
#include <list>
#include <thread>
#include <iterator>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "HitDection.h"
#include "SoundManager.h"
#include "Timer.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                                      //��Ϸ��ѭ��
private:
	std::shared_ptr<Map> map;                             //��ͼ
	std::shared_ptr<TankBase> playerTank;                 //���
	std::shared_ptr<Bullet> playerBullet;                 //����ӵ�
	std::list<std::shared_ptr<TankBase>> enemiesTank;     //�����б�
	std::list<std::shared_ptr<Bullet>> enemiesBullet;     //�����ӵ��б�
	HitDection hit;                                       //��ײ���
	SoundManager soundManager;                            //��������
	Timer t;
	void addEnemy();                                      //����һ���з�̹��
};