#pragma once

#include "struct.h"
#include "Timer.h"

class TankBase {
	friend class GameControl;
	friend class HitDection;
public:
	TankBase(int _x, int _y, Dir d, int s, int b);
	virtual ~TankBase() = default;
protected:
	virtual void move() = 0;          //̹���ƶ�
	virtual void show() = 0;          //��ʾ̹��
	void changeShape();               //�л�����
	void auto_move();                 //�����Զ��ƶ�
	void clearOld();                  //�����ͼ

	int x, y;                         //̹�ˣ����Ͻǣ�����
	Dir dir;                          //����
	bool auto_flag;                   //�Զ��ƶ����
	int speed;                        //̹���ٶ�
	int cur_shape;                    //��ǰ����
	int blood;                        //̹��Ѫ��
	Timer t;                          //��ʱ��
};

