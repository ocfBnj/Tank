#pragma once

// �����ͼ���ж����������Ƿ��ཻ
#include "Map.h"
#include <memory>
#include <list>
#include "Bullet.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

class HitDection
{
	friend class GameControl;

	HitDection(Map&);
	~HitDection() = default;

	bool isIntersect(                              //�ж����������Ƿ��ཻ
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2);
	bool dection(int x, int y, int w, int h);      //�ж��ӵ��Ƿ���ǽ��ײ
	void canGo(std::shared_ptr<TankBase>);         //�ж�̹���ܲ�����

	void player_dection(std::shared_ptr<TankBase>, //�ж����ײǽ��ײ����
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	void enemy_dection(std::shared_ptr<TankBase>,  //�жϵ���ײǽ,ײ����,ײ���
		std::shared_ptr<TankBase>,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	int focus(                                     //�ж��ӵ��Ƿ����̹��
		std::shared_ptr<TankBase>&,
		std::shared_ptr<Bullet>&,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	Map& map;                                      //��ͼ
	int map_x, map_y;                              //�Ƚ���ײʱ��ͼ�����Ͻ�����
	bool hit_flag;                                 //ײ����־��ײ������ʾ��ͼ����
};