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
	void canGo(int& x, int& y, Dir d);             //�ж�̹���ܲ�����
	int focus(                                     //�ж��ӵ��Ƿ����̹��
		std::shared_ptr<TankBase>&,
		std::shared_ptr<Bullet>&,
		std::list<std::shared_ptr<TankBase>>&,
		std::list<std::shared_ptr<Bullet>>&);

	Map& map;                                      //��ͼ
	int map_x, map_y;                              //�Ƚ���ײʱ��ͼ�����Ͻ�����
	bool hit_flag;                                 //ײ����־��ײ������ʾ��ͼ����
};