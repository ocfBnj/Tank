#pragma once

#include <graphics.h>
#include "struct.h"
#include "TankBase.h"
#include "Timer.h"
#include "Sound.h"

class TankBase;
class Bullet {
public:
	Bullet();
	void shoot(const TankBase& tank, bool is_enemy); //�����ӵ�
	bool move();                                     //�ƶ��ӵ�
	bool isExist() const;                            //����ӵ�������Ϣ
	int getRealX() const;                            //����ӵ�ʵ������
	int getRealY() const;
	int getHeight() const;
	int getWidth() const;
	Dir getDir() const;
	void adjust();                                   //��ײ�������ӵ�
private:
	IMAGE img_bullet[4];                             //�ӵ�ͼƬ
	int x, y;                                        //�ӵ������Ͻǣ���ʾ����
	int real_x, real_y;                              //�ӵ������Ͻǣ�ʵ������
	Dir dir;                                         //����
	int speed;                                       //�ӵ��ٶ�
	bool exist;                                      //�ӵ��Ƿ����
	Timer timer_shoot;                               //���˷����ӵ�Ƶ��

	void clearOld() const;                           //���������ͼ
};
