#pragma once

#include <graphics.h>
#include "struct.h"
#include "TankBase.h"
#include "Timer.h"

class TankBase;
class Bullet {
public:
	Bullet();
	void shoot(const TankBase& tank, bool is_enemy); //�����ӵ�
	bool move();                                     //�ƶ��ӵ�
	bool isExist() const;                            //����ӵ�������Ϣ
	int getX() const;
	int getY() const;
	void adjust();                                   //��ײ�������ӵ�
private:
	IMAGE img_bullet[4];                             //�ӵ�ͼƬ
	int x, y;                                        //�ӵ������Ͻǣ�����
	Dir dir;                                         //����
	int speed;                                       //�ӵ��ٶ�
	bool exist;                                      //�ӵ��Ƿ����
	Timer timer_shoot;                               //���˷����ӵ�Ƶ��

	void clearOld() const;                           //���������ͼ
};
