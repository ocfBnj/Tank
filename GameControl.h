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
	std::list<std::pair<std::shared_ptr<EnemyTank>,       //����
		std::shared_ptr<Bullet>>> enemies;
	HitDection hit;                                       //��ײ���
	SoundManager soundManager;                            //��������
	Timer t;
	size_t enemies_total;                                 //�з�ʣ��̹������

	void addEnemy();                                      //����һ���з�̹��
	void blast(int x, int y);                             //��ը��Ч

	IMAGE bumb_img[3];                                    //��ը��ͼ
	IMAGE temp;                                           //��ըǰ���������ͼ
	Timer bumb_timer;                                     //��ըʱ��
};