#pragma once

// �����ͼ���ж����������Ƿ��ཻ
#include "Map.h"
#include <memory>
#include <list>
#include "Bullet.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

class HitDection {
	friend class GameControl;
public:
	HitDection(Map&);
	~HitDection() = default;

	bool isIntersect(                              //�ж����������Ƿ��ཻ
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2);
private:
	bool blockDection(int x, int y, int w, int h);      //�ж��ӵ��Ƿ���ǽ��ײ
	void canGo(std::shared_ptr<TankBase>);         //�ж�̹���ܲ�����

	void playerDection(std::shared_ptr<TankBase>, //�ж����ײǽ��ײ����
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	void enemyDection(std::shared_ptr<TankBase>,  //�жϵ���ײǽ,ײ����,ײ���
		std::shared_ptr<TankBase>,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	int focus(                                     //�ж��ӵ��Ƿ����̹��
		std::shared_ptr<PlayerTank>&,
		std::shared_ptr<Bullet>&,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);
	void bulletDection(std::shared_ptr<Bullet>&,   //�ж��ӵ���ײ
		std::shared_ptr<Bullet>&);
private:
	Map& map;                                      //��ͼ
	int map_x, map_y;                              //�Ƚ���ײʱ��ͼ�����Ͻ�����
	bool hit_flag;                                 //ײ����־��ײ������ʾ��ͼ����
};