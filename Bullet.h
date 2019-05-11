#pragma once

#include <graphics.h>
#include <Windows.h>
#include "struct.h"
#include "Timer.h"

class Bullet {
	friend class GameControl;
	friend class HitDection;
	Bullet();

	void clearOld();                           //�����ǰλ�õ�ͼƬ
	bool shoot(int _x, int _y, Dir d, bool b); //�����ӵ�
	bool move();                               //�ƶ��ӵ�

	IMAGE img_bullet[4];                       //�ӵ�ͼƬ
	int x, y;                                  //�ӵ������Ͻǣ�����
	Dir dir;                                   //����
	int speed;                                 //�ӵ��ٶ�
	bool exist;                                //�ӵ��Ƿ����
	Timer t;                                   //��ʱ��
};
